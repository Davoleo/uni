% L'immagine underexposed.jpg è sia sovraesposta (fuori dalla finestra) che sottoesposta (interno), questo la rendere difficile da trattare
% In quanto aumentare il contrasto fuori fa perdere troppe informazioni sull'interno
% mentre aumentare la luminosità all'interno brucia i dettagli fuori dalla finestra

im = imread('underexposed.jpg');

figure(1);
imshow(im), title('immagine originale');

% gamma correction globale
im = im2double(im);

%.^ : elevami ogni elemento della matrice (invece che utilizzare il prodotto matriciale)
gamma = 0.4;
im1 = im.^gamma;

gamma = 4;
im2 = im.^gamma;

% Tramite questa operazione, siccome non è lineare, potrebbe cambiare la relazione tra i canali colore, 
% perché i 3 RGB possono essere influenzati in modo diverso dallo stesso valore di gamma
% Un modo migliore è traformare l'immagine in YCbCr e applicare la gamma correction solo al canale della luminanza

figure(2);
subplot(1,2,1), imshow(im1);
subplot(1,2,2), imshow(im2);

%Cambiamento di gamma troppo repentino => schifezza
gamma = 4*rand(size(im, 1), size(im, 2));
im3 = im.^gamma;
figure(3), imshow(im3)

%% Gamma correction adattiva
% in diverse regioni dell'immagine utilizziamo un valore di gamma diverso, in modo che si ottengano i vantaggi di entrambi i valori.

close all
clear
clc

% perciò utilizziamo il filtro gaussiano per creare un immagine maschera dove i valori sono smooth, e non cambiano repentinamente,
% ma si mantiene in media l'informazione della lightness dell'immagine.

% Artefatti possibili: halo sugli oggetti, perché se ci sono hard borders, la maschera come filtro gaussiano tende a rendere morbidi i cambiamenti.
% quindi la gamma correction schiarisce un po dove dovrebbe scurire e viceversa lungo i bordi
%  Per sistemare il problema degli halo si potrebbe applicare il filtro bilaterale.

im = imread('underexposed.jpg');
im = im2double(im);

% converto in YCbCr
Ycbcr = rgb2ycbcr(im);

% estraggo il canale Y
channelY = Ycbcr(:,:,1);

% Calcolo la maschera
mask = 1-channelY;
gaussmask = imgaussfilt(mask, 14);
figure, imshow(gaussmask)
bilatmask = imbilatfilt(mask, 10, 4);
figure, imshow(bilatmask);

% Gamma values utilizzando gaussian blur filter
gamma = (0.5 - gaussmask) / 0.5;
gaussChannelY = channelY.^(2.^gamma);

% Gamma values utilizzando bilateral filter
gamma = (0.5 - bilatmask) / 0.5;
bilatChannelY = channelY.^(2.^gamma);

% sovrascrivo il canale Y
im_gauss = Ycbcr;
im_gauss(:,:,1) = gaussChannelY;

im_bilat = Ycbcr;
im_bilat(:,:,1) = bilatChannelY;

%riconverto in RGB e mostro l'immagine
rgb_gauss = ycbcr2rgb(im_gauss);
rgb_bilat = ycbcr2rgb(im_bilat);
figure, imshow(rgb_gauss), imwrite(rgb_gauss, "processed_gauss.jpg");
figure, imshow(rgb_bilat), imwrite(rgb_bilat, "processed_bilateral.jpg");

% Consegna:
% - Codice
% - Presentazione (file documento per )
% Formato zip con dentro tutto