%% Ex. 6 - Scheda Algebra Lineare
clc
clear 
close all

A = hilb(1000);
B = rand(1000);

x = ones(1000, 1);
y = x;

b = A*x;
c = B*y;

errA = norm(abs((A\b) - x)./x)
condA = cond(A)
errB = norm(abs((B\c) - y)./y)
condB = cond(B)

conds = zeros(1, 49);
for DIM = 1:49
	conds(DIM) = cond(hilb(DIM + 1));
end

semilogy(2:50, conds);