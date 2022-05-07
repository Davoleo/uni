function x = jacobi(A, b, max_iter, treshold)
	%jacobi - Risolve il sistema tramite il Metodo Iterativo di Jacobi
	%
	% Syntax: result = jacobi(matrix, termine_noto, max_iter, tolleranza)
	%
	% Risolve il sistema Ax = b tramite Metodo Iterativo Lineare di Jacobi
	

		% In forma matriciale
		x = ones(3,1);

		D = diag(diag(A));
		C = A-D;

		Dinv = inv(D);

		B = -Dinv*C;
		q = Dinv*b;

		disp('raggio spettrale')
		norm(eig(B), "inf")

		k = 0;
		while k < max_iter && norm(b-A*x) > treshold
			x = B*x+q;
			k = k + 1;
		end	
	end