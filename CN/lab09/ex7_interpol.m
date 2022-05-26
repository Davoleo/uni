% Ex. 7 - Scheda Interpolazione
clc
clear
close all

a = -1;
b = 1;
n = 10;

% Nodi Equispaziati
xi = linspace(a, b, n+1);
% Nodi di Chebyshev
xchebi = (a+b)/2 - (b-a)/2 * cos((2*[0:n]+1) / (2*n+2) * pi);

% Valori di test
x = linspace(a,b);

for i = 1:length(x)
	omegan(i) = abs(prod(x(i) - xi));
	omegacheby(i) = abs(prod(x(i) - xchebi));
end

plot(x, omegan);
hold on
plot(x, omegacheby);


