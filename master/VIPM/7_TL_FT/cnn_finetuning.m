clear
close all
clc

rng(42)

net = alexnet;

sz = net.Layers(1).InputSize;
analyzeNetwork(net);


%% cut layers

% Prendiamo tutti i layer fino a quell prima del penultimo
layersTransfer = net.Layers(1:end-6); % TODO : Scegliere dove tagliare (original 3)
% Congeliamo i pesi di questi layer
layersTransfer = freezeWeights(layersTransfer); % <--- TBD

%% replace layers
numClasses = 10;
layers = [
	layersTransfer 
	% Permette di adattare il learning rate di questi layer come fattore del learning rate degli altri
	% In questo caso learning rate 20 volte più alto del resto della rete
	% Cosicché anche scongelando tutti i layer quelli che mi interessano imparano di più che gli altri
	fullyConnectedLayer(numClasses, 'WeightLearnRateFactor', 20, 'BiasLearnRateFactor', 20) 
	softmaxLayer 
	classificationLayer
];
%analyzeNetwork(layers)

%% preparazione dati - data loader
% Ogni volta che si termina un epoca si dovrebbero rimischiare 
% i batch in modo che 2 immagini non siano quasi mai nello stesso batch

% Usare multicore per caricare il batch (e.g. un immagine per ogni  core)

% Nel mentre la rete sta lavorando a fare backtracking si può iniziare a caricare il batch successivo

% ImageDatastore assegnerebbe in automatico le label se i file fossero in cartelle diverse per ogni classe, 
% ma nel nostro caso non è così

imds = imageDatastore('image.orig\');

% Utilizziamo il nome del file per assegnare la label manualmente
labels = [];
for ii=1:size(imds.Files, 1)
	name=imds.Files{ii, 1}; % cella ii
	% Splitta il path del file in path / nome / estensione
	[p, n, ex]=fileparts(name);
	class=floor(str2double(n)/100);
	labels = [labels; class];
end

labels = categorical(labels);
imds = imageDatastore('image.orig\', 'Labels', labels);

%% divisione train/test/validation
% Split randomico tra training e test (tenendo conto di ogni label)
[imdsSemi, imdsTest] = splitEachLabel(imds, 0.8, 'randomized');
[imdsTrain, imdsVal] = splitEachLabel(imdsSemi, 0.85, 'randomized');

%% data augmentation
% non abbiamo tantissimi dati, trainare 60M di parametri senza congelare pesi abbiamo bisogno di fare data augmentation
pixelRange=[-2 2];
imageAugmenter=imageDataAugmenter( ...
	'RandXReflection', true,       ...
	...'RandXTranslation', pixelRange,... % Traslazione random di -2 +2 pixel [asse X]
	...'RandYTranslation', pixelRange, ...% Traslazione random di -2 +2 pixel [asse Y]
	'RandRotation', [-10, 10], ...
	'RandXScale', [0.9, 1.1], ...
	'RandYScale', [0.9, 1.1] ...
);

% Image data store che contiene le immagini con la data augmentation
% Passiamo anche come info la size che ci serve per la rete
% Passiamo il dataset di training
% La lista di trasformazioni possibili
augimdsTrain = augmentedImageDatastore(sz(1:2), imdsTrain, "DataAugmentation", imageAugmenter);
augimdsVal = augmentedImageDatastore(sz(1:2), imdsVal);
augimdsTest = augmentedImageDatastore(sz(1:2), imdsTest);

%% configurazione fine-tuning
options = trainingOptions(		...
	'sgdm',						...
	'MiniBatchSize', 15,		... % TODO TBD
	'MaxEpochs', 6, 			... % TODO TBD
	'InitialLearnRate', 1e-4,	... % TODO TBD
	'shuffle', 'every-epoch',	...
	'ValidationData', augimdsVal,...% TODO TBD :check: - Al momento si sta utilizzando il test set come validation non è proprio ottimale ma okay
	'ValidationFrequency', 3,...
	'ValidationPatience', 15, ...
	'Verbose', false,...
	'Plots', 'training-progress' ...
);

%% training
netTransfer = trainNetwork(augimdsTrain, layers, options);

%% test
tic
% Otteniamo anche la score oltre alla predizione così è possibile fare un treshold in cui la rete invece che fare una predizione 
[lab_pred_te, scores] = classify(netTransfer, augimdsTest);
toc

%% Valutazione performance
acc = numel(find(lab_pred_te==imdsTest.Labels))/numel(lab_pred_te)