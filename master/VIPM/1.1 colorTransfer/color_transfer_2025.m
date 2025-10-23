close all
clear all
clc

im = imread("colorTransfer/image1.png")

% prima riga
r1 = im(1, :, :);
% prima colonna
c1 = im(:, 1, :);

% prime 10 righe e 10 colonne
q = im(1:10, 1:10, :);

% Visualizzazione canali immagine
figure(1), imshow(im(:, :, 1)), title('canale R')
figure(2), imshow(im(:, :, 2)), title('canale G')
figure(3), imshow(im(:, :, 3)), title('canale B')
figure(4), imshow(im)


close all

figure(5)
subplot(1,4,1), imshow(im(:, :, 1))
subplot(1,4,2), imshow(im(:, :, 2))
subplot(1,4,3), imshow(im(:, :, 3))
subplot(1,4,4), imshow(im)

close all

% ---------------------
%% Color Transfer
% Y CbCr - Separa la luminanza Y dai canali colore CbCr
% noi vogliamo trasportare

im1 = imread("colorTransfer/image1.png");
im2 = imread("colorTransfer/image2.png");

figure(1), imshow(im1);
figure(2), imshow(im2);

% convertiamo le immagini in valori double tra 0 e 1 (normalizzazione)
im1 = im2double(im1);
im2 = im2double(im2);

% dimensioni delle immagini
S1 = size(im1);
S2 = size(im2);

% convertiamo le immagini in YCbCr da RGB
im1_ycbcr = rgb2ycbcr(im1);
im2_ycbcr = rgb2ycbcr(im2);

% trasformazione dell'immagine in 3 colonne (3 canali) utilizzando reshape (non so quante righe verranno, quindi metto [])
im1_ycbcr = reshape(im1_ycbcr, [], 3);
im2_ycbcr = reshape(im2_ycbcr, [], 3);
% estrazione di statistiche (media sulle 3 colonne)
stat_im1 = mean(im1_ycbcr);
stat_im2 = mean(im2_ycbcr);

%% fare in modo che im1_ycbcr abbia le stesse statistiche 

% Centrare i valori annullando la media
im1_ycbcr(:, 2) = im1_ycbcr(:, 2) - stat_im1(2);
im1_ycbcr(:, 3) = im1_ycbcr(:, 3) - stat_im1(3);

% Utilizzo la media della nuova immagine come nuovi valori
im1_ycbcr(:, 2) = im1_ycbcr(:, 2) - stat_im2(2);
im1_ycbcr(:, 3) = im1_ycbcr(:, 3) - stat_im2(3);

% ricomposizione delle immagini
im1_ycbcr = reshape(im1_ycbcr, S1);
im2_ycbcr = reshape(im2_ycbcr, S2);

% trasformo di nuovo in RGB
im1_rgb = ycbcr2rgb(im1_ycbcr);
im2_rgb = ycbcr2rgb(im2_ycbcr);

% trasformo in uint8, da double
im1_rgb = im2uint8(im1_rgb)
im2_rgb = im2uint8(im2_rgb)
figure(3), imshow(im1_rgb)
figure(4), imshow(im2_rgb)

imwrite(im1_rgb, 'im1_trasformata.png')
imwrite(im2_rgb, 'im2_trasformata.png')

% Assignment 1 parte 1: Trovare un'altra coppia di immagini  su cui questa elaborazione funziona