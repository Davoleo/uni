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