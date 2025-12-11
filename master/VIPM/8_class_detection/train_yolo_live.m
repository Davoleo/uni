% imageLabeler per annotare le immagini con delle bounding box.
% 
% Bias:
% Nel dataset non ci sono presenti delle immagini con oggetti multiclasse all'interno, 
% quindi il modello tenderà a classificare solo un oggetto per immagine in generale

% imds: ImageDataStore
% blds: BoxLabelDatastore
[imds, blds] = objectDetectorTrainingData(gTruth);

ds = combine(imds, blds);
inputSize = [224 224 3];
% Definiamo una trasformazione che prenderà in input il datastore e una funzione di preprocessing custom
trainingDataForEstimation = transform(ds, @(data)preprocessData(data, inputSize));

%% YOLO : Unica passata per fare classificazione di oggetti
% - Divide l'immagine in maniera regolare e per ognuna di queste regioni fa delle proposte di oggetti 
% 									andando a modificare nelle regioni per matchare la ground truth
% - Improvement: invece che usare regioni quadrate per le ground truth si usa una regione tipica che si avvicina di più alla sagoma dell'oggetto da riconoscere
numAnchors = 6;
[anchors, meanIoU] = estimateAnchorBoxes(trainingDataForEstimation, numAnchors);
area = anchors(:, 1).*anchors(:, 2);
[dummy, idx] = sort(area, 'descend');
anchors = anchors(idx, :);
anchorBoxes = {anchors(1:3, :); anchors(4:6, :)};

% La versione di YOLO di MATLAB è abbastanza vecchia solo ver (1 2 3 4 e X [la quale ha bisogno di 7 ore di GPU con almeno 12GB di RAM])
% --- L'ultima versione di YOLO al momento è la 12

%% detector
classes = {'Farfalla', 'Cane', 'Ragno'};
% In YOLO all'interno della stessa versione ci sono diverse dimensioni del modello
% - Quello più piccolo si chiama tiny in questo caso pre-addestrato su dataset coco, (si fa solo finetuning)
detector = yolov4ObjectDetector("tiny-yolov4-coco", classes, anchorBoxes, "InputSize", inputSize);

options = trainingOptions("sgdm", ...
	InitialLearnRate=0.001, ...
	MiniBatchSize=16, ...
	MaxEpochs=50, ...
	ResetInputNormalization=false, ...
	VerboseFrequency=1, ...
	Shuffle='every-epoch' ...
);
trainedDetector = trainYOLOv4ObjectDetector(ds, detector, options);

%% Predict on image
I = imread('...');
I = imresize(I, inputSize(1:2));
[bboxes, scores, labels]=detect(trainedDetector, I, threshold=0.05);
detectingImg = insertObjectAnnotation(I, 'Rectangle', bboxes, labels);
figure(1), clf
imshow(detectedImg)

%% predict on training set images
ims = dir('dataset_detection_minimal');
for ii=4:size(ims, 1)
	I = imread([ims(ii, 1).folder filesep ims(ii, 1).name]);
	I = imresize(I, inputSize(1:2));
	[bboxes, scores, labels]=detect(trainedDetector, I, threshold=0.05);
	detectedImg = insertObjectAnnotation(I, 'Rectangle', bboxes, labels);
	%detectedImg = imresize(detectedImg, 4)
	figure(1), clf
	imshow(detectedImg)
	waitforbuttonpress
end