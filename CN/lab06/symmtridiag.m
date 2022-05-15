function matrix = symmtridiag(size, diag0, diag1)
%symmtridiag - Costruisce una matrice quadrata tridiagonale simmetrica
%
% Syntax: matrix = symmtridiag(size, diag, diag1)
%
% Costruisce una matrice quadrata size x size tridiagonale con diagonale principale uguale a diag e prime sopra/sotto diagonali uguali a diag1
	matrix = zeros(size);
	matrix = matrix + diag(diag1, -1) + diag(diag0) + diag(diag1, 1);
end