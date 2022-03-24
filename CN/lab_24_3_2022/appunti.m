clc
clear
close all

% Esercizi Scheda 2
% 5)

% Genero la matrice A come da consegna
A = eye(9,9).*-2 + diag(ones(1,8),-1) + diag(ones(1,8), 1)
% Scambio le righe 3 e 6
temp = A(3,:);
A(3,:) = A(6,:);
A(6,:) = temp

% Scambio le colonne 1 e 4
temp = A(:,1);
A(:,1) = A(:,4);
A(:,4) = temp

pause
clc
clear

% 6)
% Definisco la matrice A come da consegna
A = [[1:4];[5:8];[9:12]]

% significati dei comandi:
% restituisce la grandezza della matrice A in un vettore riga di 2 colonne
% i 2 valori sono rispettivamente il numero di rige e di colonne della matrice A
size(A);

% Moltiplica tutti i valori della matrice A per se stessi (elemento per elemento), i valori risultanti sono posizionati nella matrice B
B=A.*A;

% Moltiplicazione righe/colonne tra la matrice A e se stessa
% Impossibile perché se la matrice A è di grandezza 3x4 allora la matrice in seconda posizione deve essere di grandezza 4x3
B=A*A;

% Moltiplicazione righe/colonne tra la matrice A e se stessa trasposta
% Siccome una delle 2 matrici A è trasposta le grandezze sono compatibili, ed è quindi possibile effettuare il prodotto righe/colonne
% Siccome gli input sono nel formato 4x3*3x4 Il risultato sarà in formato 4x4
B=A'*A

% 5 Statement di selezione diversi:
% 1. Seleziona le prime 2 righe della 4 colonna della matrice A
% 2. Seleziona tutte le righe della terza colonna della matrice A
% 3. Seleziona le prime 2 righe di tutte le colonne di A
% 4. Seleziona tutte le righe delle colonne 2 e 4 della matrice A
% 5. Crea un vettore riga con i valori: A(2, 1) A(3, 1) A(3, 1) | di default MATLAB prende la prima colonna implicitamente
A(1:2,4), A(:, 3), A(1:2, :), A(:, [2 4]), A([2 3 3]);

% Sostituisce il valore nella terza riga della seconda colonna di A con il valore della prima riga e colonna di A
A(3,2)=A(1,1);

% Sostituisce i valori delle prime 2 righe della quarta colonna di A con degli 0
% il vettore costruito da zeros deve essere in formato colonna per funzionare correttamente
A(1:2,4)=zeros(2,1);

% Assegna alla seconda riga della matrice A, I valori stessi ma diminuiti di: 
% 		valore di seconda riga e prima colonna fratto il valore in prima riga e colonna moltiplicato per ognuno dei valori della prima riga della matrice
% Nota: si tratta del Primo passo dell'eliminazione di Gauss, dove il moltiplicatore è A(2,1)/A(1,1)
A(2,:)=A(2,:)-A(2,1)/A(1,1)*A(1,:);
% Passo 2
A(3,:)=A(3,:)-A(3,1)/A(1,1)*A(1,:);

pause
clc
clear

% 7) 
% Definisco la matrice A come da consegna
A = ones(8).*[1:8]';
% Definisco le matrici triangolari superiori e inferiori a partire da A
S = triu(A);
I = tril(A);

% Modifico la diagonale principale di S annullando i valori 
% Sottraendo ad S la matrice diagonale formata dalla diagonale di S
S = S - diag(diag(S));
% Modifico la diagonale principale di I rendendo i valori uguali a 1
% Sottraendo ad I la matrice diagonale formata dalla diagonale di I
%   con i valori diminuiti di 1
I = I - diag(diag(I) - 1);

% Matrice tridiagonale con elementi di A
B1 = diag(diag(A, -1), -1) + diag(diag(A)) + diag(diag(A, 1), 1)
% Matrice bidiagonale superiore con elementi di A
B2 = diag(diag(A)) + diag(diag(A, 1), 1)
% Matrice bidiagonale inferiore con elementi di A
B3 = diag(diag(A, -1), -1) + diag(diag(A))
