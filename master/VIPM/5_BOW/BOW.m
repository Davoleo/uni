% statefile = fullfile('.', 'RNGState.mat');
% data = load(statefile);
% state = data.state;
% rng(state)
rng(159)

clc
clear
close all

disp("creazione griglia")

pointPositions = [];
featStep = 8; %! La griglia su cui estrarre le feature è resa molto spessa in modo da ottenere più dettagli possibili
imsize = 256; %! Le immagini sono sempre 256x384 o 384x256

tic
for ii = featStep:featStep:imsize-featStep
	for jj = featStep:featStep:imsize-featStep
		pointPositions=[pointPositions; ii jj];
	end
end
toc

%% estrazione features
disp('estrazione features')

%! Standard Ratio 80%:20% -> More training samples -> Better accuracy overall (similar variance in evaluation during training)
Nim4training = 80;

features = [];
labels = [];
tic
for class=0:9
	for nimage=0:Nim4training-1
		im=im2double(imread(['image.orig/' num2str(100*class+nimage), '.jpg']));
		
		% croppo l'immagine con dimensioni pari al minimo tra le due, in modo che la dimensione maggiore sia tagliata mantenendo il contenuto centrale
		%padding = floor((size(im, 1:2)-imsize)/2);
		%im=im(padding(1)+1:padding(1)+imsize, padding(2)+1:padding(2)+imsize, :);
		
		%! Sia il crop che il resize mantendo un padding di pixel neri come bande ai lati per evitare stretching dell'immagine ha dato risultati peggiori
		% I test sono mantenuti commentati sopra e sotto per permettere di essere provati
		im=imresize(im, [imsize imsize]);

		% Resize while keeping ratio
		% realsize = size(im, 1:2);
		% scale = min(imsize/realsize(2), imsize/realsize(1));
		% im = imresize(im, scale);
		im=rgb2gray(im);

		% realsize = size(im, 1:2);
		% impadded = zeros(imsize);
		% impadded(imsize/2+(1:realsize(1))-floor(realsize(1)/2), ...
		% imsize/2+(1:realsize(2))-floor(realsize(2)/2))=im;

		% specifichiamo il metodo perché di default non sa inferirlo senza usare la detect
		% il sottoinsieme di punti ridotto di quelli sul bordo non mi interessa per come sono stati calcolati i punti quindi dontcare
		% ! Qui se si utilizza rescaling mantenendo il ratio è necessario cambiare il parametro dell'immagine a 'impadded'
		[imfeatures,dontcare] = extractFeatures(im, pointPositions, 'Method', 'SURF');
		features = [features; imfeatures];
		% per ogni riga (descrittore) costruiamo una colonna con le categorie e il numero dell'immagine
		labels = [labels; repmat(class,size(imfeatures, 1), 1) repmat(nimage, size(imfeatures, 1), 1)];
	end
end
toc

%% creazione del vocabolario
disp('kmeans')
% 100 parole
K = 1000 %! Buon compromesso tra il numero di classi e un numero medio di 100 visual words per immagine
tic
% Clusterizzare le feature in K cluster
%[IDX, C] = kmeans(features, K, "MaxIter", 2000, "Display", "final");
%* ^ Disabilitato per performance reasons, i risultati sono salvati dentro C.mat e IDX.mat
%*   scommentare per eseguire kmeans from scratch

% Load previously computed kmeans output
load C.mat
load IDX.mat

toc

%% istogrammi BOW training
disp('rappresentazione BOW training');
BOW_tr = []; 
labels_tr = [];

tic
for class=0:9
	for nimage=0:Nim4training-1
		% posizioni u in cui la prima colonna corrisponde alla classe che stiamo valutando 
		% e la seconda colonna corrisponde all'immagine che stiamo valutando
		u=find(labels(:,1) == class & labels(:, 2) == nimage);
		% features in posizione u (immagine con relativa categorizzazione [label])
		imfeaturesIDX = IDX(u);
		% rappresentazione con istogramma della frequenza delle feature all'interno di questo elem
		% hist: Decide il passo dell'istogramma da solo e sceglie se tagliare inizio / fine, 
		% 	tramite il secondo parametro forziamo la rappresentazione di tutti e K i valori 
		H = hist(imfeaturesIDX, 1:K);
		% normalizziamo l'istogramma in modo che la somma sia 1
		% -> possiamo confrontare anche immagini con grandezze diverse 
		%* Questa norma ha dato risultati leggermente migliori (0.5% improvements)
		H = H ./ (norm(H) + eps);
		BOW_tr = [BOW_tr; H];
		labels_tr = [labels_tr; class];
	end
end
toc

%% classificatore
disp('classifier')
% input: BOW_tr e labels_tr

%* Less accurate than SVMs most times
%knn = fitcknn(BOW_tr, labels_tr, NumNeighbors=12, Distance="euclidean");

%! SVM non-lineare è il classificatore che ha dato i risultati migliori
template = templateSVM("KernelFunction", "rbf", "KernelScale", "auto", "Standardize", true, "BoxConstraint", 8);
SVM = fitcecoc(BOW_tr, labels_tr, "Learners", template, "Coding", "onevsall", "Verbose", 1);


%% istogrammi BOW test
disp('rappresentazione BOW test')
BOW_te = [];
labels_te = [];

tic
for class=0:9
	for nimage=Nim4training:99
		im=im2double(imread(['image.orig/' num2str(100*class+nimage), '.jpg']));

		%* cropping
		% croppo l'immagine con dimensioni pari al minimo tra le due, in modo che la dimensione maggiore sia tagliata mantenendo il contenuto centrale
		%padding = floor((size(im, 1:2)-imsize)/2);
		%im=im(padding(1)+1:padding(1)+imsize, padding(2)+1:padding(2)+imsize, :);

		%* resize (stretch)
		im=imresize(im, [imsize imsize]); % TBD provare a fare crop invece che resize (stretch)

		%* resize (maintain ratio) [part 1]
		% realsize = size(im, 1:2);
		% scale = min(imsize/realsize(2), imsize/realsize(1));
		% im = imresize(im, scale);
		im=rgb2gray(im);

		%* resize (maintain ratio) [part 2]
		% realsize = size(im, 1:2);
		% impadded = zeros(imsize);
		% impadded(imsize/2+(1:realsize(1))-floor(realsize(1)/2), ...
		% imsize/2+(1:realsize(2))-floor(realsize(2)/2))=im;

		% specifichiamo il metodo perché di default non sa inferirlo
		% il sottoinsieme di punti ridotto di quelli sul bordo non mi interessa per come sono stati calcolati i punti quindi dontcare
		[imfeatures,~] = extractFeatures(im, pointPositions, 'Method', 'SURF');

		% Distanze di ogni punto della matrice dall'altro punto dell'altra matrice.
		% Se le parole nel vocabolario diventano molto la grandezza di d potrebbe esplodere
		D = pdist2(imfeatures, C);
		% per ogni riga di D la posizione del minimo definisce qual è il cluster più vicino e quindi quello a cui viene assegnato.
		[dontcare, words] = min(D, [], 2);
		% dontcare perché non mi interessa il valore del minimo ma solo l'indice del minimo riga per riga (seconda dimensione).
		H = hist(words, 1:K);
		H = H ./ (norm(H) + eps);
		BOW_te = [BOW_te; H];
		labels_te = [labels_te; class];
	end
end
toc

%% classificazione del test set
% Applicazione di nearest neighbor per la classificazione (rubo la classe dell'elemento più vicino del training set)
disp("classificazione del test set")
% predicted_class = [];
% tic
% for ii = 1:size(BOW_te, 1)
% 	H = BOW_te(ii, :);
% 	DH = pdist2(H, BOW_tr);
% 	% Trovo vettore di training con la distanza minima
% 	u = find(DH==min(DH));
% 	% Se ne escono più di uno prendo il primo (edge case)
% 	u = u(1);
% 	predicted_class = [predicted_class; labels_tr(u)];
% end
% toc

predicted_class_svm = predict(SVM, BOW_te);
%predicted_class_knn = predict(knn, BOW_te);

%% misurazione performance

% Confusion Matrix
CM = confusionmat(labels_te, predicted_class_svm);
CM = CM./repmat(sum(CM, 2), 1, size(CM, 2));
CM

% Calcolo dell'accuracy
accuracy = mean(diag(CM))

% Assignment 5: Scadenza 2 settimane
% Modificare i TODO in modo di arrivare nel range 75-80% di accuracy 
% possibile arrivare anche fino a 85%
% estremamente difficile arrivare sopra 85%