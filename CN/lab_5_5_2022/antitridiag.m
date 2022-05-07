function M = antitridiag(n)
%antitridiag - Genera una matrice anti-tridiagonale
%
% Syntax: M = antitridiag(n)
%
% Genera una matrice che ha come anti-tridiagonale una striscia di 2 e di -1 che wrappano

	mones = ones(1, n-1) * -1;
	twos = ones(1, n) * 2;

	A = diag(mones, -1) + diag(twos) + diag(mones, 1);

	M = flip(A);
	
end

