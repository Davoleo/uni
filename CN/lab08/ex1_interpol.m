%% Ex. 1 - Scheda Interpolazione 
clc;
clear;
close all;

grado = 5;

lin = linspace(0, 2);

fx = exp(lin) .* sin(2*lin);

subplot(1,2,1);
plot(lin, fx);
title('f(x)');

px = polyfit(lin, fx, grado);
subplot(1,2,2);
parr = polyval(px, lin);
plot(lin, parr);

hold on;

lin2 = linspace(0,2, grado+1);
plot(lin2, polyval(px, lin2), '.');
title('p(x)');