clc
clear
close all

%% lettura immagini
boxImage = imread('img/stapleRemover.jpg');
sceneImage = imread('img/clutteredDesk.jpg');

%% keypoint detection
% Si fanno detection e description separate perché è possibile utilizzare algoritmi diversi
boxPoints = detectSURFFeatures(boxImage);
scenePoints = detectSURFFeatures(sceneImage);

figure(1), clf;
imshow(boxImage), hold on
plot(selectStrongest(boxPoints,100)), hold off

figure(2), clf;
imshow(sceneImage), hold on
plot(selectStrongest(scenePoints,100)), hold off

%% keypoint description
% Restituisce le descrizioni dei punti e una versione aggiornata della lista dei punti
% Vengono rimossi anche i punti il cui cerchio (intorno di certezza) finisce fuori dall'immagine (non validi per la detection)
[boxFeatures, boxPoints] = extractFeatures(boxImage, boxPoints);
[sceneFeatures, scenePoints] = extractFeatures(sceneImage, scenePoints);

%% features matching
% Su ogni riga abbiamo una coppia di punti che hanno matchato:
% Sulla prima cella abbiamo l'indice del keypoint nel template, mentre nella seconda l'indice del keypoint all'interno della scena
boxPairs = matchFeatures(boxFeatures, sceneFeatures);
% PRendiamo solo le righe di boxPoints indicizzate dalla prima colonna delle pairs
matchedBoxPoints = boxPoints(boxPairs(:,1), :);
matchedScenePoints = scenePoints(boxPairs(:, 2), :);
showMatchedFeatures(boxImage, sceneImage, matchedBoxPoints, matchedScenePoints, ...
	'montage');

%% Geometric consistency check
% tform è la trasformazioni che la estimate ha trovato
[tform, inlierBoxPoints, inlierScenePoints] = estimateGeometricTransform(matchedBoxPoints, matchedScenePoints, 'affine');
showMatchedFeatures(boxImage, sceneImage, inlierBoxPoints, inlierScenePoints, ...
	'montage');

%% bounding box drawing
boxPoly = [1 1;
	size(boxImage,2) 1;
	size(boxImage,2) size(boxImage, 1);
	1 size(boxImage, 1);
	1 1
];

newBoxPoly = transformPointsForward(tform, boxPoly);
figure(5), clf
imshow(sceneImage), hold on
line(newBoxPoly(:, 1), newBoxPoly(:, 2), 'Color', 'y');
hold off

%% more precise bounding box
figure(6), clf
imshow(boxImage);
[x,y]=ginput(4);
x=[x;x(1)];
y=[y;y(1)];

newBoxPoly = transformPointsForward(tform, [x y]);
figure(7), clf
imshow(sceneImage), hold on
line(newBoxPoly(:, 1), newBoxPoly(:, 2), 'Color', 'y');
hold off

% Assignment:
% Trovare l'elefante 
% (possibile aumentare la tolleranza geometrica per permettere una maggior trasformazione dell'oggetto).
% Il geometric consistency check (RANSAC) è random e quindi può dipendere dalle run.
% Consegna: Il codice