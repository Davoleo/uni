function x = forward_substitution(A, b)
%forward_substitution - Calcola la soluzione di un sistema lineare tramite il metodo di sostituzione in avanti
%
% Syntax: x = forward_substitution(A, b)
%
% Calcola la soluzione del sistema lineare "A b = x" con A triangolare inferiore
	% Grandezza della matrice (quadrata quindi butto il secondo termine di grandezza)
	[n, ~] = size(A);

	% Passo 1
	x(1) = b(1) / A(1,1);

	% Passo 2..n
	for i = 2:n
		% Calcolo parte del risultato x con: b - prod. scalare tra riga corrente di A (tutte le colonne fino alla diagonale principale) 
		% e i vecchi valori di x fino al passo precedente quello corrente, dividendo tutto per il valore sulla diagonale di A in posizione corrente
		x(i) = (b(i) - A(i,1:i-1) * x(1:i-1)') / A(i, i);
	end
end