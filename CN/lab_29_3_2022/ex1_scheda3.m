%% Ex 1 Scheda 3
clc
clear
close all

% Funzione A
testv = linspace(0, 1, 101);
fa = ((1 - testv ./ 24)./(1 + testv./24 + testv.^2./384)).^8;
subplot(1,3,1);
plot(testv, fa)
title('Fun 1')
ylabel('fa(x)')

% Funzione A
subplot(1,3,2)
testb1 = linspace(-2, 0, 101);
testb2 = linspace(0, 2, 101);
fb1 = (2 - testb1.^2 / 2).^2;
fb2 = (testb2.^2 / 2 + 2).^2;
fb = [fb1 fb2];
plot([testb1, testb2], fb);
title('Fun 2')
ylabel('fb(x)')

% Funzione A
subplot(1,3,3);
testc1 = linspace(-pi, 0, 101);
testc2 = linspace(0, pi, 101);
fc1 = exp(-testc1.^2);
fc2 = cos(testc2);
fc = [fc1 fc2];
plot([testc1, testc2], fc);
title('Fun 3')
ylabel('fc(x)')
