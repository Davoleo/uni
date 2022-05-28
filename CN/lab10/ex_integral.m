%% Esercizio di Integrazione
%clc
clear
close all

% Intervallo di integrazione
a = 0;
b = 2*pi;

% Funzione
f = @(x) x .* exp(-x) .* cos(2*x);

% Numero di sottointervalli
m = 100;

% Ampiezza
H = (b-a) / m;

% Intervallini di uguale grandezza (m+1 punti -> m intervalli)
interv = linspace(a, b, m+1);
i = 1:m;

%% Formula del punto medio composita
% Valutazione di f nel punto medio degli intervallini
fvalues = f((interv(i) + interv(i+1)) / 2);
% Somma di tutte le valutazioni moltiplicate per l'ampiezza dell'intervallino
Q0 = H * sum(fvalues)

%% Formula del trapezio composita
fvalues = f(interv(1)) + f(interv(end)) + 2*sum(f(interv([2:end-1])));
Q1 = H/2 * sum(fvalues)

%% Formula di Cavalieri-Simpson
fvalues = f(interv(i)) + 4*f((interv(i)+interv(i+1)) / 2) + f(i+1);
Q2 = H/6 * sum(fvalues)

matlab_ver = integral(f, a, b)