%% Ex 2 Scheda 3
clc
clear
close all

for m = 1:6
	testvec1 = linspace(-m, 0, 50);
	testvec2 = linspace(0, m, 50);
	fpart1 = (m - testvec1.^2 / m).^m;
	fpart2 = (testvec2.^2 / m + m).^m;
    % Grafico con scala logaritmica sull'asse delle Y
	%semilogy([testvec1 testvec2], [fpart1 fpart2])
	% Grafico in finestre separate
	subplot(2, 3, m);
	plot([testvec1 testvec2], [fpart1 fpart2])
    title(m)
	grid on
    hold on
end