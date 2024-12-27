%% Ex. 5 - Scheda Algebra Lineare

Test = antitridiag(8)

dets = zeros(1, 50);
conds = zeros(1, 50);

for n = 1:50
	A = antitridiag(n);
	
	dets(n) = det(A);
	conds(n) = cond(A);
end

subplot(1,2,1);
plot([1:50], dets);
title("Determinanti")

subplot(1,2,2);
plot([1:50], conds);
title("Condizionamenti")