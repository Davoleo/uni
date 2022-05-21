%% Ex. 4 - Scheda Interpolazione
clc
clear
close all;

nodes = 22;

x = linspace(-1, 1, nodes);
sinx = polyfit(x, sin(x), nodes-1);
tildesinx = polyfit(x, sin(x) .* (1 + (-1).^[1:nodes] * 10^-4), nodes-1)
polysin = polyval(sinx, x);
polytildesin = polyval(tildesinx, x);
figure('NumberTitle', 'off', 'Name', 'Interpolazione funzione sin(x)', 'Position', [200 200 800 400])

plot(x, polysin, '.')
hold on
plot(x, polysin)
title('sin(x)', 'interpreter', 'latex');
hold on;
plot(x, polytildesin)

legend('punti di interpolazione', 'polinomio interpolatore', 'polinomio interpolatore perturbato');

err = norm(abs(polysin - sin(x)))
tildeerr = norm(abs(polytildesin - sin(x)))