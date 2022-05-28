%% Esercizio 5 - Scheda Interpolazione
clc
clear
close all

gradi = [10 15 20];

xspace = linspace(-1, 1);
f = @(x) exp(x) + 1;

for g = gradi
	%x = linspace(-1, 1, g+1);
	x = cos((2*[0:g]+1)*pi / (2*g+2));

	fdirty = @(x) f(x) + (-1).^[1:g+1] * 10^-5;

	V = vander(x);
	% Termine noto del sistema
	y = f(x);
	
	ydirty = fdirty(x);

	% Trovo i coefficienti del polinomio
	a = V\y';
	adirty = V\ydirty';

	%length(a)

	subplot(1,3, (g-5)/5)
	plot(x, polyval(a, x), '*', xspace, polyval(a, xspace));
	hold on
	plot(xspace, polyval(adirty, xspace));
	hold on
	plot(xspace, f(xspace));

	legend('Punti Interpolanti', 'Polinomio interpolatore', 'Polinomio Perturbato', 'Funzione Originale')

	g
	coeff_err = max(a-adirty)
	poly_err = max(polyval(a, xspace) - polyval(adirty, xspace))

end