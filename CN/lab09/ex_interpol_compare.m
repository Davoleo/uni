%% Esercizio di Confronto tra interpolazioni composte
clc
clear
close all

% interpolazione composita lineare: 'interp1'
% interpolazione tramite spline: 'spline'

x = [-55:10:65];
y = [-3.25, -3.37, -3.35, -3.2, -3.12, -3.02, -3.02, -3.07, -3.17, -3.32, -3.3, -3.22, -3.1];
n = 12;


xspace = linspace(-55, 65);


%% Interpolazione semplice
coeff = polyfit(x, y, n);
yspace = polyval(coeff, xspace);
plot(x, y, '.', xspace, yspace, '-');
legend('punti di interpolazione', 'polinomio interpolatore');
title('Interpolazione Semplice');

%% Interpolazione Composita lineare
figure;
yspace = interp1(x, y, xspace);
plot(x,y,'o', xspace, yspace, '-');
legend('punti di interpolazione', 'polinomio interpolatore');
title('Interpolazione Composita lineare');

% Interpolazione tramite spline
figure;
yspace = spline(x, y, xspace);
plot(x, y, 'o', xspace, yspace, '-')
legend('punti di interpolazione', 'polinomio interpolatore');
title('Interpolazione Tramite Spline');