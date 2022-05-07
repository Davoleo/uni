% Esercizio Scheda_2 
% 1.a)
x = [-3, 5, 8, 0, 1, 5, -2, 4];

x(6) = 100;

x(1:3) = [5, 6, 7];

x = [x(1:3), x(5:end)];
% ^ alternativo: x(4) = []

x = x(1:3);

x = [1, 2, 3, x];

x = [x, 10, 11, 12];

%%%

% 1.b)
A = eye(4);

A(1, 1) = A(3, 4);

% [r, c] = size(A)
A = [ones(4, 1),A];

A = [A,ones(4, 1)];

A = [ones(1, 6)*4;A];

A = [A; ones(1, 6)*4];

A = [A(1:2,:);A(4:end,:)];

A = [A(:,1:2), A(:, 4:end)];
%^ alternativo A(:, 3) = []

%%%% ------------------------------------------ %%%%

% Es 2
x = [1:-0.1:0];

% mostra elementi di x in posizione 1 4 e 3
x([1 4 3])
% elementi con indice 1 3 5 7 e 10 sostituiti con un vettore riga di 5 zeri
x([1:2:7 10])=zeros(1,5);
% elementi 1 2 e 5 sostituiti con un vettore riga di 2 valori = 0.5 + un
% valore 0.3
x([1 2 5])=[0.5*ones(1,2) -0.3];
% memorizzo in y i valori di x ma in ordine inverso
y=x(end:-1:1);


%% Operazioni su vettori e matrici
x = [1:5];
y = [3 2 1 0 0];
%moltiplicazione di un vettore per 2
x*2
% somma di vettori
x+y
% moltiplicazione tra vettori (di tipo matrice)
x*y
% operazione puntuale (element-wise multiplication of vectors)
x.*y
% prodotto tra matrici (tra vettori) -> prodotto scalare
x*y'
% radice quadrata di ogni elemento
sqrt(x)

A = ones(3);
B = ones(3) * 2;

% divisione puntuale
B./A


