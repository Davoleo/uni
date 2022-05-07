function x = gauss_seidel(A, b, max_iter, treshold)
%gauss_seidel - Computes the solution of the system using Gauss-Seidel Method
%
% Syntax: x = gauss_seidel(matrix, termine_noto, max_iter, tolleranza)
%
% Computes the solution of the system A*x = b using Gauss-Seidel Method

	[n, ~] = size(A);

	x = ones(n,1);

	D = diag(diag(A));
	E = tril(A, -1);
	F = A - D - E;

	B = -inv(E+D)*F;
	q = inv(E+D)*b;

	disp('raggio spettrale')
	norm(eig(B), "inf")

	iter = 0;
	while iter < max_iter && norm(b-A*x) > treshold
		x = B * x + q;
		iter = iter + 1;
	end

	% Per componenti
	%{

	iter = 0;
	while iter < max_iter
		x_prev = x;

		for i = 1:n
			sum = 0;
			for j = 1:i-1
				sum = sum + A(i,j) * x(j);
			end
			for j = i+1:n
				sum = sum + A(i,j) * x_old(j);
			end

			x(i) = (b(i) - sum) / A(i,i);
		end		
		iter = iter + 1;
	end
	%}
end