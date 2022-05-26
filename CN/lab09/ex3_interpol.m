%% Ex. 3 - Scheda Interpolazione
clc
clear
close all 

% Griglia per valutazione errore
x = linspace(-3, 3);

% Le 2 funzioni da testare
f = @(x) exp(x) .* cos(4*x);
%f = @(x) abs(x-1);

k = 0;
% nodi di Interpolazione
for n = [5, 10, 20, 40]
	k = k + 1;
	% GRiglia di Interpolazione
	space = linspace(-3, 3, n);
	ys = f(space);

	% Matrice di Vandermonde
	van = vander(space);
	coeffs = van\ys';

	y_interp = polyval(coeffs, x);
	y_exact = f(x);
	% errore
	errf(k) = norm(abs(y_interp - y_exact), 'inf');
end

plot(x, polyval(coeffs, x));
hold on;
plot(x, f(x));
hold on;
plot(space, polyval(coeffs, space), '*');

legend('polinomio interpolatore', 'funzione', 'punti di interpolazione')
grid on

figure
plot([1:k], errf)
title('Grafico Errore')
xlabel('numero di nodi')
grid on