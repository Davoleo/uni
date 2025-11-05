close all
clear
clc

% Lettura immagine
% Questa immagine viene caricata come uint16 e quindi tutti i colori finiscono schiacciate nella zona scura
% Questo significa che il sensore supporta 16 bit
% inoltre mancano i 3 canali colore, apparentemente, anche se in realtà ci sono.
im = imread("RAWinput/IMG_1295ss.tiff");
figure(1), imshow(im)

% conversione in double nel range [0 1]
% Riporta in 0-1 qualunque siano gli uint utilizzati all'interno dell'immagine
im = im2double(im);

% Auto exposure (finto)
% Divido l'immagine per il massimo contenuto all'interno dell'immagine
% - massimo sull'immagine con i due punti permette di trattarlo come un vettore riga
im = im./max(im(:));    % Equivalente a max(max(im))
% Quando si usa una figura già aperta è meglio usare clf per pulire la figura
% In questo modo si può vedere il bayer pattern zoommando sull'immagine 
figure(1), clf, imshow(im);

%% Demosaicing (demosaiking) ------------------------
% Versione stupida (dimezza la risoluzione dell'immagine sia in altezza che in larghezza)
% Configurazione del sensore (Bayer Pattern)
% R G R G
% G B G B
% R G R G
% G B G B

% Rosso: Prendo tutte le righe dalla prima all'ultima con passo 2, righe dispari
% R = im(1:2:end, 1:2:end);
% Blu: Righe e colonne pari
% B = im(2:2:end, 2:2:end);
% Green: Colonne pari e righe dispari o viceversa
% G = im(1:2:end, 2:2:end);

R = zeros(size(im, 1)-2, size(im, 2)-2);
G = zeros(size(im, 1)-2, size(im, 2)-2);
B = zeros(size(im, 1)-2, size(im, 2)-2);

for y = 2:size(im, 1)-1
	for x = 2:size(im, 2)-1
		% 3x3 matrix window
		w = im(y-1:y+1, x-1:x+1);

		if mod(y, 2) == 1 && mod(x, 2) == 1
			% Red Channel
			R(y-1,x-1) = w(2,2);
			G(y-1,x-1) = mean([w(1,2), w(3,2), w(2,1), w(2,3)]);
			B(y-1,x-1) = mean([w(1,1), w(1,3), w(3,3), w(3,1)]);
		elseif mod(y, 2) == 0 && mod(x, 2) == 0
			% Blue channel
			R(y-1,x-1) = mean([w(1,1), w(1,3), w(3,3), w(3,1)]);
			G(y-1,x-1) = mean([w(1,2), w(3,2), w(2,1), w(2,3)]);
			B(y-1,x-1) = w(2,2);
		elseif (mod(y, 2) == 0 && mod(x, 2) == 1)
			% Green channel part 1
			R(y-1,x-1) = mean([w(3,3), w(3,1)]);
			G(y-1,x-1) = w(2,2);
			B(y-1,x-1) = mean([w(1,1), w(1,3)]);
		elseif (mod(y, 2) == 1 && mod(x, 2) == 0)
			% Green channel part 2
			R(y-1,x-1) = mean([w(1,1), w(1,3)]);
			G(y-1,x-1) = w(2,2);
			B(y-1,x-1) = mean([w(3,3), w(3,1)]);
		end
	end
end

% Immagine = concatenazione sulla terza dimensione di R G e B
im = cat(3,R,G,B);
figure(2), imshow(im)

% Abbiamo una dominante verde causata dal fatto che i filtri per come sono costituiti all'interno della camera tendono a creare valore più alti.
% - Bisogna moltiplicare le componenti rosso e blu per un valore in modo che siano bilanciati (nelle camere questo è effettuato automaticamente perché la compagnia conosce i propri filtri)
% - Nel nostro caso applichiamo AWB (con l'algoritmo gray-world)

% Gray world: La media dei colori deve essere grigio -> quindi i valori di compensazione per R e B sono quelli che rendono grigio il verdone che
% altrimenti viene creato da questa immagine essendo sbilanciata

%% AWB ########################
S = size(im);
% REshape in 3 colonne una per ogni colore
im = reshape(im, [], 3);

% Gray world (GW) --------------
media = mean(im);
% coefficienti  di correzione
% Ogni canale viene diviso per la media e viene ingrandito più/meno a seconda di quanto colore è presente.
coeffgw = [0.5, 0.5, 0.5]./media;
% Per ogni canale moltiplico per il coefficiente di correzione
% im(:, 1) = im(:, 1)*coeff(1);
% oppure applico correzione diagonale creando una matrice diagonale in cui i 3 valori di correzione sono sulla diag principale
%  in questo caso il primo valore sulla diagonale sarà moltiplicato per il primo canale
% im = im*diag(coeffgw);
mean(im);

% White Patch (WP) -------------
maxx = max(im)
for i = 1:3
	im(:,i) = im(:, i)./maxx(i);
end
max(im)

% Riformo l'immagine con la sua size originale
im = reshape(im, S);
figure(3), imshow(im)

%% sRGB Color Correction ---------------------
% Utilizzando il macbeth color checker nell'immagine possiamo costruire una matrice 24x3 dei valori all'interno dell'immagine
% Prendere una matrice 24x3 dei colori target veri del macbeth color checker
% noi dobbiamo trovare la matrice 3x3 che moltiplicata per la matrice dei colori dell'immagine ci da quelli del macbeth target.

% Color correction
RGBt = [
	116,81, 67;
	199,147,129;
	91, 122,156;
	90, 108,64;
	130,128,176;
	92, 190,172;
	224,124,47;
	68, 91, 170;
	198,82, 97;
	94, 58, 106;
	159,189,63;
	230,162,39;
	35, 63, 147;
	67, 149,74;
	180,49, 57;
	238,198,20;
	193,84, 151;
	0,  136,170;
	245,245,243;
	200,202,202;
	161,163,163;
	121,121,122;
	82, 84, 86;
	49, 49, 51;
];
% 0-1 normalization
RGBt = RGBt./255;

% Matrice 24x3 dei valori RGB camera della color checker. 
RGBc = []; 
%im_checker = imcrop(im); % Crop della color checker dell'immagine per avere una versione piccola da manipolare
im_checker = im(990:1039, 1750:1832, :);
im_checker = imresize(im_checker, 5); % Ingrandiamolo di 5 perché abbiamo precedentemente dimezzato la risoluzione dell'intera immagine

figure(4), imshow(im_checker)
% Si aspetta 24 click sull'immagine per ogni colore del color checker
% [x,y] = ginput(24);
% save coordinateColorChecker.mat x y
% possono essere salvate in un file .mat utilizzando il comando save nomefile x y
load coordinateColorChecker.mat

x = round(x);
y = round(y);
rad = 2; % Dimensione intorno su cui fare la media.
for ii=1:24
	% y identifica la riga | x identifica la colonna
	color_crop = im_checker(y(ii)-rad:y(ii)+rad, x(ii)-rad:x(ii)+rad, :);
	color_crop = reshape(color_crop, [], 3);
	% Siccome scriviamo le righe di questa matrice in un loop, si aumenta sempre di più la size, che è inefficiente in MATLAB, preallocando sarebbe più efficiente
	% Ma in questo caso non cambia molto visto che la matrice è molto piccola
	RGBc = [RGBc; mean(color_crop)];
end

% Per trovare la matrice 3x3 c'è da risolvere il sistema Ax = B
% (RGBc_T * RGBc)^-1 * (RGBc_T * RGBc) *  M  =  X   * RGBc_T * RGBc
%                      (24x3   * 24x3) *[3x3]=[3x3] * 24x3 * 3x24

M = inv(RGBc'*RGBc) * (RGBc'*RGBt); % matrice pseudo-inversa

im = reshape(im, [], 3);
im = im * M;
im = reshape(im, S);
figure(4), imshow(im)

%% Image Enhancement ---------------------------
% Saturation factor -> Increase image saturation
Sfactor = 1.15;

% conversione a HSV
im = rgb2hsv(im);
% Moltiplichiamo il canale di saturazione
im(:,:,2) = im(:,:,2) * Sfactor;
% TODO : Optional - aumento del contrasto.
% conversione in RGB
im = hsv2rgb(im);

% Compressione e salvataggio immagine
% Se l'immagine finisce per essere troppo pesante per l'assignemnt si può comprimere con
% im = resize(im, 0.5) 
imwrite(im2uint8(im), 'immagine_raw_to_srgb.jpg');

% Password Code = vipM2526