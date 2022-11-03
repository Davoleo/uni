% introduco un vettore riga di 3 elementi
a=[1,2,3,4]
% vettore colonna
c=[1;2;3;4]
% aggiunge un elemento al vettore riga a (con valore pi-greco)
d=[a, pi]

% trasposizione del vettore d (diventa un vettore colonna)
d'

% valore memorizzato in d alla posizione 3
d(3)
% ultima posizione
d(end)

% lunghezza di un vettore
length(d)

% Esempio matrice 2x3
A=[3,1,2;4,3,4]

% size(A) length 
size(A)

% modifica di matrice
A = [A; sqrt(2), 2, 4]

% accesso dati matrice
A(2, 2)
% all the cells of the first row
A(1,:)
% all the cells of the third column
A(:, 3)

A' %%trasposizione matrice

% vettore riga di 10 elementi (1-10)
f=1:10
% vettore vuoto (perché di default MATLAB va di passo +1)
%f=10:1
%versione corretta
f=10:-1:1
%passo 2
f=2:2:10

linspace(0,10,11)
%tutte le righe -- colonne da 2 a 3
A(:, 2:3)

A(1:2:3, 2:3)

%matrice identità  
%4x4
eye(4)

%Matrice 2x2 di numeri 1
ones(2)
%altro esempio
ones(3, 1)
% matrice di zeri
zeros(3)

% matrice 2x2 di numeri casuali
rand(2)

%estrae la diagonale di A
diag(A)
%prima sopra-diagonale (nel caso di una matrice 3x3 ha 2 elementi)
diag(A, 1)
%prima sotto-diagonale (nel caso di una matrice 3x3 ha 2 elementi)
diag(A, -1)

%diag può anche essere usato per creare una matrice quadrata diagonale con
%il vettore passato come parametro come K-esima diagonale
diag(v)

% triangolare superiore di A
triu(A)
% triangolare inferiore di A - partendo dalla prima sopradiagonale
tril(A, 1)
