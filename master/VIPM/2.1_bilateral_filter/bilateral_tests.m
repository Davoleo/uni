close all
clear
clc

im = imread("MaroonBells.jpg");
im = im2double(im);

figure(1);
imshow(im), title('immagine originale');

figure(2);
im_gaussian = imgaussfilt(im, 15);
imshow(im_gaussian), title('filtraggio gaussiano')

figure(3)

% per subplot (Quante zone sulle righe, quante zone sulle colonne, selezione della zona dove disegnare)
% Il contatore sceglierà la zona dove disegnare dinamicamente.
counter = 1;
for ii = [0.01 0.05 0.1 0.2 0.5]
	for jj = [1 2 3 4 5]
		tic
		im_b = imbilatfilt(im, ii, jj);
		toc
		subplot(5, 5, counter), imshow(im_b), drawnow
		counter = counter + 1;
	end
end

% MATLAB per evitare di perdere tempo deferra le chiamate di drawing tutte alla fine, quando i contatori sono già al valore massimo, 
% Per forzare il comportamento si può utilizzare il comando "drawnow" 

figure(4)
% Fa la media solo dei valori dei pixel che sono abbastanza vicini (0.1), mettendolo più alto 
% si può far comportare il filtro bilaterale come se fosse un gauss perché considera più estensione di colori come "mergiabili"
% tuttavia a livello computazionale il filtro fa comunque i controlli sulla lontanaza dei pixel, rendendolo più pesante
im_b = imbilatfilt(im, 0.1, 15);
imshow(im_b), title('filtro bilaterale')