%% Ex 3 Scheda 3
clc
clear
close all

% Vector of dots to draw
t = linspace(0, 2*pi, 361);
% Functions to compute x and y based on the dots offset
xt = 3 + 6 * cos(t);
yt = 8 + 6 * sin(t);
plot(xt, yt)
title('Ellipse')
axis square
% ^ makes sure the axis are square so we actually realize it's an ellipse and not a weird circle