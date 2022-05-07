
function x = jacobi_comp(x0, A, b, max_iter, treshold)
%jacobi - Risolve il sistema tramite il Metodo Iterativo di Jacobi
%
% Syntax: result = jacobi(x0, matrix)
%
% Risolve il sistema Ax = b tramite Metodo Iterativo Lineare di Jacobi

	% Size della matrice
	[n, ~] = size(A);

	x = zeros(n, 1);
	xprec = x0;

	k = 1;
	%abs(X(k+1, :) - X(k, :)) < treshold
	while k < max_iter && norm(b - A * x) > treshold
		for i = 1:n
			s = 0;
			for j = 1:n
				if j ~= i
					s = s + A(i,j) * xprec(j);
				end
			end
			x(i) = (s - b(i)) / -A(i,i);
			xprec = x;
		end

		k = k + 1;
	end

end