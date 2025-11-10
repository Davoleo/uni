clc
clear
close all

%% lettura immagini
elephantImage = imread('img/elephant.jpg');
sceneImage = imread('img/clutteredDesk.jpg');

%% keypoint detection
% Si fanno detection e description separate perché è possibile utilizzare algoritmi diversi
elephantPoints = detectSURFFeatures(elephantImage, MetricThreshold=700);
scenePoints = detectSURFFeatures(sceneImage);

figure(1), clf;
imshow(elephantImage), hold on
plot(selectStrongest(elephantPoints,100)), hold off

figure(2), clf;
imshow(sceneImage), hold on
plot(selectStrongest(scenePoints,100)), hold off

%% keypoint description
% Restituisce le descrizioni dei punti e una versione aggiornata della lista dei punti
% Vengono rimossi anche i punti il cui cerchio (intorno di certezza) finisce fuori dall'immagine (non validi per la detection)
[elephantFeatures, elephantPoints] = extractFeatures(elephantImage, elephantPoints);
[sceneFeatures, scenePoints] = extractFeatures(sceneImage, scenePoints);

%% features matching
% Su ogni riga abbiamo una coppia di punti che hanno matchato:
% Sulla prima cella abbiamo l'indice del keypoint nel template, mentre nella seconda l'indice del keypoint all'interno della scena
elephantPairs = matchFeatures(elephantFeatures, sceneFeatures, MaxRatio=0.8);
% PRendiamo solo le righe di elephantPoints indicizzate dalla prima colonna delle pairs
matchedElephantPoints = elephantPoints(elephantPairs(:,1), :);
matchedScenePoints = scenePoints(elephantPairs(:, 2), :);
showMatchedFeatures(elephantImage, sceneImage, matchedElephantPoints, matchedScenePoints, ...
	'montage');

%% Geometric consistency check
% tform è la trasformazioni che la estimate ha trovato
[tform, inlierElephantPoints, inlierScenePoints] = estimateGeometricTransform(matchedElephantPoints, matchedScenePoints, 'affine', MaxNumTrials=5000);
showMatchedFeatures(elephantImage, sceneImage, inlierElephantPoints, inlierScenePoints, ...
	'montage');

%% bounding elephant drawing
elephantPoly = [1 1;
	size(elephantImage,2) 1;
	size(elephantImage,2) size(elephantImage, 1);
	1 size(elephantImage, 1);
	1 1
];

newElephantPoly = transformPointsForward(tform, elephantPoly);
figure(5), clf
imshow(sceneImage), hold on
line(newElephantPoly(:, 1), newElephantPoly(:, 2), 'Color', 'y');
hold off

%% more precise bounding elephant
figure(6), clf
imshow(elephantImage);
% [x,y]=ginput(30);
% x=[x;x(1)];
% y=[y;y(1)];
load coordinateBB.mat

newElephantPoly = transformPointsForward(tform, [x y]);
figure(7), clf
imshow(sceneImage), hold on
line(newElephantPoly(:, 1), newElephantPoly(:, 2), 'Color', 'y');
hold off

% Assignment:
% Trovare l'elefante 
% (possibile aumentare la tolleranza geometrica per permettere una maggior trasformazione dell'oggetto).
% Il geometric consistency check (RANSAC) è random e quindi può dipendere dalle run.
% Consegna: Il codice