function x = reverse_substitution(A, b)
%reverse_substitution - Calcola la soluzione del sistema per sostituzione all'indietro
%
% Syntax: x = reverse_substitution(A, b)
%
% Calcola la soluzione del sistema "A x = b" tramite metodo di sostituzione all'indietro (A deve essere triangolare superiore)
	% Grandezza della matrice (quadrata quindi butto il secondo termine di grandezza)
	[n, ~] = size(A);

	% Passo 1
	x(n) = b(n) / A(n,n);

	% Passo n-1..1
	for i = n-1:-1:1
		x(i) = (b(i) - A(i, i+1:n) * x(i+1:n)') / A(i, i);
	end


end