%% Scheda 4 Ex 1
clc
clear
close all

figure('Renderer', 'painters', 'Position', [200 200 800 400])

subplot(1, 2, 1);
x = linspace(-4, 8, 200);
pcoeff = [1 -6 11 -6];
roots(pcoeff)
plot(x, polyval(pcoeff, x))
title('p(x)')
z1=fzero(@(x) x.^3 - 6*x.^2 + 11*x - 6, 0)
z2=fzero(@(x) x.^3 - 6*x.^2 + 11*x - 6, 4)
z3=fzero(@(x) x.^3 - 6*x.^2 + 11*x - 6, 1.6)


subplot(1, 2, 2);
ptildex = x.^4 - 7*x.^3 + 15*x.^2 - 13*x + 4;
plot(x, ptildex)
title('p~(x)')


roots([1,-7,15,-13,4])

fzero(@(x) x.^4 - 7*x.^3 + 15*x.^2 - 13*x + 4, 20)