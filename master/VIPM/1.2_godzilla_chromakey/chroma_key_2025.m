close all
clear
clc

% Per fare chromakey è importante che le immagini siano della stessa grandezza (dobbiamo lavorare con una maschera pixel per pixel)
im1 = im2double(imread('godzilla_1.jpg'));
im2 = im2double(imread('godzilla_2.jpg'));
S1 = size(im1);

imshow(im1);

% crop interattivo
%crop = imcrop(im1);
% crop automatico
crop1 = im1(452:452+125, 397:397+32, :);
crop2 = im1(128:128+125, 372:372+32, :);
crop = [crop1, crop2];

figure(2), imshow(crop);
% Reshape in colonne con, canale R, G, B
model = reshape(crop, [], 3); % <--------- TBD: Definizione modello, si possono aggiungere più crop al modello
% Teniamo solo i valori unici di riga.
model = unique(model, 'rows');

im1 = reshape(im1, [], 3);
% preparazione della maschera, a 0
Mask = zeros(size(im1));
% treshold
T = 0.15; % <-------- TBD: Definizione soglia

% tramite ciclo for
tic
for ii = 1:size(im1, 1)
	d = repmat(im1(ii, :), size(model, 1), 1) - model;
	d = sqrt(sum(d.^2, 2)); % Distanza euclidea
	if min(d) > T
		Mask(ii, :) = 1;
	end
end
tempoFor=toc;

% Creazione di maschera
Mask = zeros(size(im1));
tic
% Calcola le distanze di tutte i pixel dell'immagine dai valori dei pixel nel modello
d = pdist2(im1, model);
% Indicizzo le righe della maschera che corrispondono a valori che nella distanza sono maggiori al treshold
Mask(min(d, [], 2) > T, : ) = 1;
tempoVec = toc;

[tempoFor, tempoVec]

% 
Mask = reshape(Mask, S1);
im1 = reshape(im1, S1);

figure(1), clf
subplot(1,3,1), imshow(im1)
subplot(1,3,2), imshow(Mask)
subplot(1,3,3), imshow(im2)

im3 = im1.* Mask + im2 .* (1-Mask);
figure(2), imshow(im3)

imwrite(im3, 'chromakey.png')


% color transfer (extra)
im3 = im2double(im3); S3 = size(im3); im3_ycbcr = rgb2ycbcr(im3);
im2 = im2double(im2); S2 = size(im2); im2_ycbcr = rgb2ycbcr(im2);

% Columns
im3_ycbcr = reshape(im3_ycbcr, [], 3);
im2_ycbcr = reshape(im2_ycbcr, [], 3);
mean_im3 = mean(im3_ycbcr);
mean_im2 = mean(im2_ycbcr);

% Neutralize mean
im3_ycbcr(:, 2) = im3_ycbcr(:, 2) - mean_im3(2);
im3_ycbcr(:, 3) = im3_ycbcr(:, 3) - mean_im3(3);
% apply new mean
im3_ycbcr(:, 2) = im3_ycbcr(:, 2) + mean_im2(2);
im3_ycbcr(:, 3) = im3_ycbcr(:, 3) + mean_im2(3);

% go back, go back, go back
im3_ycbcr = reshape(im3_ycbcr, S3); im3_rgb = ycbcr2rgb(im3_ycbcr); im3_rgb = im2uint8(im3_rgb);
im2_ycbcr = reshape(im2_ycbcr, S2); im2_rgb = ycbcr2rgb(im2_ycbcr); im2_rgb = im2uint8(im2_rgb);
figure(3), imshow(im3_rgb)

imwrite(im3_rgb, 'chromakey+colotransfer.png')


% Assignment 1 (parte 2): Modificare il modello trovando un buon valore della treshold e utilizzando crop diversi per fare un buon chroma key
% - Optional: trasferire i colori dell'immagine di arrivo sull'immagine di partenza.
% - Consegna: Codice e immagine risultato.