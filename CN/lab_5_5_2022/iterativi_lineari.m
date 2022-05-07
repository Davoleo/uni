clc
clear
close all

A = [
	3 0 4;
	7 4 2;
	-1 -1 -2; ];
B = [
	-3 3 -6;
	-4 7 -8;
	5 7 -9; ];
C = [
	4 1 1;
	2 -9 0;
	0 -8 -6; ];
D = [
	7 6 9;
	4 5 -4;
	-7 -3 8; ];

b = A * [5 4 7]';
x0 = ones(3,1);

x = jacobi(A, b, 20, 10^-5);
err = norm([5 4 7]' - x)

x = gauss_seidel(A, b, 100, 10^-5);
err = norm([5 4 7]' - x)