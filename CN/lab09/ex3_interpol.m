%% Ex. 3 - Scheda Interpolazione
%clc
clear
close all 

x = linspace(-3, 3);

% Le 2 funzioni da testare
%f = @(x) exp(x) .* cos(4*x);
f = @(x) abs(x-1);

nodes = 20;
space = linspace(-3, 3, nodes);
ys = f(space);

van = vander(space);
coeffs = van\ys';

plot(x, polyval(coeffs, x));
hold on;
plot(x, f(x));
hold on;
plot(space, polyval(coeffs, space), '*');

y_interp = polyval(coeffs, x);
y_exact = f(x);
errf = norm(abs(y_interp - y_exact), 'inf')