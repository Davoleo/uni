%% Esercizio sui mimini quadrati (Lab 10)
%clc
clear
close all;


sigma = [0.00 0.06 0.14 0.25 0.31 0.47 0.60 0.70];
epsilon = [0.00 0.08 0.14 0.20 0.23 0.25 0.28 0.29];

coeff = polyfit(sigma, epsilon, 2);

den = (length(sigma)*sum(sigma.^2) - (sum(sigma)^2));
q = (sum(epsilon).*sum(sigma.^2)-sum(sigma)*(sum(sigma.*epsilon)))./den;
m = ((length(sigma)*sum(sigma.*epsilon)) - sum(sigma) * sum(epsilon))...
./den;

previsione = polyval(coeff, 0.9)

plot(sigma, epsilon, '*');
hold on;
x = linspace(0.00, 0.9);
plot(x, polyval(coeff,x));