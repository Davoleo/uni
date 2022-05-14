%% Ex. 1 - Scheda Algebra Lineare

DIM = 10;

%adiag = [3,4,3];
%adiagoff = [3,2];
adiag = rand(1, DIM);
adiagoff = rand(1, DIM-1);
A = diag(adiag) + diag(adiagoff, -1) + diag(adiagoff, +1);

% Step 0
d0 = 1;
d = zeros(1, DIM);

% Step 1 & 2
d(1) = adiag(1);
d(2) = d(1) * adiag(2) - adiagoff(1) * adiagoff(1) * d0;

% Step 3..DIM
for k = 3:DIM
	d(k) = d(k-1)*adiag(k) - adiagoff(k-1)*adiagoff(k-1)*d(k-2);
end

udiag = zeros(1, DIM);
udiag(1) = d(1) / d0;
for n = 2:DIM
	udiag(n) = d(n) / d(n-1);
end

ldiag = ones(1, DIM);
ldiagoff = zeros(1, DIM-1);
ldiagoff(1) = adiagoff(1) * d0 / d(1);
for n = 2:DIM-1
	ldiagoff(n) = adiagoff(n) * d(n-1) / d(n);
end

% Debug Prints
%udiag
%ldiag
%ldiagoff

det = prod(d);
if abs(det) < 10^-15
	disp(['La matrice ha un determinante vicino a 0: ' num2str(det) ' -> la fattorizzazione LU potrebbe non essere corretta']);
end

L = diag(ldiag) + diag(ldiagoff, -1);
U = diag(udiag) + diag(adiagoff, +1);

Atilde = L*U;

err = norm(abs(A - Atilde))
