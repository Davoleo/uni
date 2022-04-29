%% Ex. 1

size = 10;
symmtridiag(size, rand(1, size) * 10, rand(1, size-1) * 10);


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