%% Ex. 2 - Scheda Interpolazione
clc;
clear;
close all;

grado = 5;

% Con Nodi Equispaziati
a = -grado;
b = +grado;
lin = linspace(a, b);


runge = 1 ./ (1 + lin.^2);

figure('NumberTitle', 'off', 'Name', 'Interpolazione Funzione di Runge', 'Position', [200 200 800 400])

subplot(1,2,1);
plot(lin, runge);
title('Nodi Equispaziati');

hold on;
px = polyfit(lin, runge, grado);
parr = polyval(px, lin);
plot(lin, parr);

hold on;
lin2 = linspace(a,b, grado+1);
plot(lin2, polyval(px, lin2), '.');

legend('runge(x)', 'polinomio interpolatore', 'punti di interpolazione');

% Con nodi di Chebyshev
cheby_end = 20;
%Nodi Chebyshev
cheby=(a+b)/2 - (b-a)/2 * cos((2*[0:cheby_end]+1) / (2*cheby_end+2) * pi);
chebyrunge = 1 ./ (1 + cheby.^2);

pxcheby = polyfit(cheby, chebyrunge, cheby_end);
subplot(1,2,2);
plot(lin, runge);
hold on;
plot(lin, polyval(pxcheby, lin));
hold on;
plot(lin2, polyval(pxcheby, lin2), '.');
title('Nodi di Chebyshev');

legend('runge(x)', 'polinomio interpolatore', 'punti di interpolazione');