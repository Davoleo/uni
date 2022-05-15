%% Ex. 1

size = 10;
symmtridiag(size, rand(1, size) * 10, rand(1, size-1) * 10);

pause

%% Ex. 2
clear
clc
format long

% Sostituzione in avanti
n = 100;
A = tril(rand(n));
b = rand(n,1);
x = forward_substitution(A, b)';

residuo = norm(A*x-b)
condi = cond(A)

% Sostituzione all'indietro
% Random Numbers
% A = triu(rand(n));
A = eye(n) + diag(ones(n-1, 1) * 2, 1);
yexact = ones(n,1);
b = A * yexact;
y = reverse_substitution(A, b)';

% residuo = norm(A*y-b)
err = norm(y - yexact)

condi = cond(A)

pause

%% Ex. 4
clc
clear

A = [ 2 3 1;
	  1 -1 1;
	  0 2 2  ];
B = [ 1 2 1;
	 -1 2 -1;
	  2 0 2 ];
C = [ 1 0 1;
	  0 1 1;
	  1 0 2 ];

% Per valutare Se sono diverse si può anche fare la norma della differenza tra le 2 matrici risultanti
% > Se è zero -> Le 2 matrici sono uguali
% Rimuovere ';' per confrontare i 2 risultati
AB = A*B;
BA = B*A;
if norm(AB - BA) ~= 0
	disp('AB e BA sono diverse');
end

% Rimuovere ';' per confrontare i 2 risultati
ApBpC = (A + B) + C;
BpCpA = A + (B + C);
if norm(ApBpC - BpCpA) == 0
	disp('AB e BA sono uguali');
end

% Rimuovere ';' per confrontare i 2 risultati
BCA = A * (B * C);
ABC = (A * B) * C;
if norm(ABC - BCA) == 0
	disp('A(BC) e (AB)C sono uguali');
end

% Rimuovere ';' per confrontare i 2 risultati
ABtrasp = (A*B)';
BtraspAtrasp = B'*A';
if norm(ABtrasp - BtraspAtrasp) == 0
	disp("(AB)' e B'A' sono uguali");
end
