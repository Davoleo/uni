close all
clear
clc

net = alexnet;
% Genera struttura della rete e la mostra
% Vediamo i layer della rete con un nome per ogni layer (e.g. Conv3 o Pool4) 
% 272(S) x 272(S) x 3(C) x 1(B) | Dove le dimensioni corrispondono a: spatial, channels, batch 
% 	Nel layer di convoluzione si trova anche una sorta di pooling perché le size sono diverse 
analyzeNetwork(net);

%%
size = net.Layers(1).InputSize;
layer = 'conv1';

%% 
im = imread('peppers.png');

% La rete si aspetta valori double 0-255 tutto il resto della
% normalizzazione se lo fa internamente
im = double(imresize(im, size(1:2)));
% 55x55x96 (dimensioni dell'immagine dopo il primo layer di convoluzione)
% possono esserci qualsiasi numero (positivi/negativi) non è ancora applicata ReLU -> 
% Quindi se dobbiamo visualizzare non si riuscirebbe

% Stiamo tirando fuori direttamente le feature dalla funzione d'attivazione della rete
feat = activations(net, im, layer);
% Se vogliamo tirare fuori i risultati con una forma diversa possiamo usare OutputAs
% feat = activations(net, im, layer, "OutputAs", "rows");

% comando per fare l'autoscaling dei valori per poter visualizzare anche la parte negativa
figure(1), clf
for ii=1:25
	subplot(5,5,ii)
	% imagesc: ti sto passando valori che non sono tipici valori delle immagine -> riscala in automatico tra 0-1
	% colormap: setto la colormap in scala di grigi
	% drawnow: obbligo a disgnare ora
	imagesc(feat(:,:, ii)), colormap gray, drawnow
end

% Vediamo che ha tirato fuori bordi dell'immagine in diversi orientamenti diverso spessore, 
% in altri filtri ha fatto versioni differenti delle immagini tagliando valori invertendo ecc...

% Stesso dataset, però stavolta tiriamo fuori le feature attraverso questa rete neurale -> Più efficiente.

%% estrazione feature sul training set

layer = 'relu7';

feat_tr = [];
labels_tr = [];
Nim4training = 70;

tic
for class=0:9
	for nimage=0:Nim4training-1
		disp([num2str(class) ' ' num2str(nimage)])
		im = double(imread(['image.orig\' num2str(class*100+nimage) '.jpg']));
		% Resize nella stessa dimensione che la rete si aspetta
		im = imresize(im, size(1:2));
		feat_temp = activations(net, im, layer, "OutputAs", "rows");
		% Ogni volta copia l'array aggiungendo le nuove feature e cancella quello vecchio -> inefficient
		feat_tr = [feat_tr; feat_temp];
		labels_tr = [labels_tr; class];
	end
end
toc

%% estrazione feature sul test set

feat_te = [];
labels_te = [];

tic
for class=0:9
	for nimage=Nim4training:99
		disp([num2str(class) ' ' num2str(nimage)])
		im = double(imread(['image.orig\' num2str(class*100+nimage) '.jpg']));
		% Resize nella stessa dimensione che la rete si aspetta
		im = imresize(im, size(1:2));
		feat_temp = activations(net, im, layer, "OutputAs", "rows");
		% Ogni volta copia l'array aggiungendo le nuove feature e cancella quello vecchio -> inefficient
		feat_te = [feat_te; feat_temp];
		labels_te = [labels_te; class];
	end
end
toc

%% normalizzazione features
% relu7 non normalizzato: 0.8967
% relu7 non normalizzato: 0.9433

norm(feat_tr(1,:))
norm(feat_te(1,:))

% Per fare in modo che le feature siano più comparabili
feat_tr = feat_tr./sqrt(sum(feat_tr.^2,2));
feat_te = feat_te./sqrt(sum(feat_te.^2,2));

norm(feat_tr(1,:))
norm(feat_te(1,:))

%% classificazione 1-NN
% Distanze di tutti gli elementi della matrice da tutti gli elementi dell'altra (di default distanza euclidea)
D = pdist2(feat_te, feat_tr);
% non ci interessa la distanza minima ma solo l'indice in cui si trova
[dummy, idx_pred_te] = min(D, [], 2);
% Andiamo a prendere il label di training dell'elemento con la distanza minima
lab_pred_te = labels_tr(idx_pred_te);
% Calcolo dell'accuracy (quante volte le label matchano quelle di test)
acc = numel(find(lab_pred_te == labels_te)) / numel(labels_te)

% In generale più due dataset sono simili più funzioneranno meglio le feature verso la fine della rete CNN
% Meno sono simili più funzionano meglio le feature iniziali della rete
% Assignment: Provare a tagliare la rete in 3 punti diversi per vedere come cambia l'outcome
	% 1 taglio verso l'inizio | 1 taglio verso la metà | 1 taglio verso la fine ||> Si possono fare le prove anche senza normalizzare
	% Extra: Cambiare il classificatore da 1-NN -> ... (e.g. SVM) | 