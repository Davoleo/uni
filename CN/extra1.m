clc
clear
close all

figure('Renderer', 'painters', 'Position', [200 200 800 400])

%% Esercizi extra 5/04/2022

% Creazione matrice Identità 4x4
A = eye(4);
% Diagonale con soli '4', moltiplicando la matrice per 4 puntualmente
A = A.*4;
% Vettore colonna b contenente 1 2 3 4
b = [1:4]';
% Risolvo il sistema Ax = b
x = A\b;
% Elemino l'ultima (quarta) colonna di A
A(:,4) = [];
% Setto i valori della prima riga a 1
A(1,:) = ones(1,3);
% Printo la size di A
sizeOfA = size(A)

% Grafico della funzione x^4+2x^2+sin(5)
subplot(1, 2, 1)
x = linspace(-5,5, 200);
f1 = x.^4 + 2*x.^2 + sin(5);
plot(x, f1);
title('$$x^4 + 2x^2 + \sin(5)$$', 'interpreter', 'latex')
xlabel('x')
ylabel('f1(x)')

% Sottografico con la funzione x^3 + 2x - 2
subplot(1, 2, 2)
f2 = x.^3 + 2*x - 2;
plot(x, f2);
title('$$x^3 + 2x - 2$$', 'interpreter', 'latex')
xlabel('f2(x)')