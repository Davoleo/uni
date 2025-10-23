% Per fare chromakey è importante che le immagini siano della stessa grandezza (dobbiamo lavorare con una maschera pixel per pixel)
im1 = im2double(imread('godzilla_chromakey/godzilla_1.jpg'));
im2 = im2double(imread('godzilla_chromakey/godzilla_2.jpg'));
S1 = size(im1);

imshow(im1);

% crop interattivo
%crop = imcrop(im1);
% crop automatico
crop = im1(1:10, 1:10, :);
figure(2), imshow(crop);
% Reshape in colonne con, canale R, G, B
model = reshape(crop, [], 3); % <--------- TBD: Definizione modello, si possono aggiungere più crop al modello
% Teniamo solo i valori unici di riga.
model = unique(model, 'rows');

im1 = reshape(im1, [], 3);
% preparazione della maschera, a 0
Mask = zeros(size(im1));
% treshold
T = 0.3; % <-------- TBD: Definizione soglia

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

im3 = im1.* M + im2 .* (1-M);
figure(2), imshow(im3)

% Assignment 1 (parte 2): Modificare il modello trovando un buon valore della treshold e utilizzando crop diversi per fare un buon chroma key
% - Optional: trasferire i colori dell'immagine di arrivo sull'immagine di partenza.
% - Consegna: Codice e immagine risultato.