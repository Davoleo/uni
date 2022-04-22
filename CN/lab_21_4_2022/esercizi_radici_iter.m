%% Calcolo della radice di cos(2x)^2-x^2
% appartenente all'intervallo [0,1.5]

%% Metodo Di Newton
clc
clear
close all

fun = @(x) cos(2*x).^2 - x.^2;
deriv_fun = @(x) -4 * cos(2*x) * sin(2*x) - 2*x;

x0 = 0.7;
max_iter = 100;
thres = 10^(-5);

[approx, n_iter] = newton(x0, fun, deriv_fun, thres, max_iter, false);

disp('num iterazioni' + n_iter);
approx

x_plot = linspace(-1.5, 1.5);

plot(x_plot, fun(x_plot));
grid on;

% Confronto con Metodo built-in di MATLAB
root = fzero(fun, x0);
err = abs(root - approx);
% Nuovo grafico
figure;
semilogy([1:n_iter+1], err, '-*');
pause;

%% Metodo di Bisezione
clc
clear
close all

thres = 10^-5;
a=0;
b=1.5;

err = 1;
i=1;
while err > thres
	mid = (a+b)/2;
	if (cos(2*mid)^2 - a^2)*(cos(2*mid)^2-mid^2) < 0
		b=mid;
	elseif (cos(2*mid)^2 - a^2)*(cos(2*mid)^2-mid^2) == 0
		disp('mid è radice');
		return;
	else
		a=mid;
	end
	err = abs(b-a);		% Criterio specifico per il metodo di bisezione
	e(i) = err;
	i = i+1;
end

semilogy(e);
mid

pause;

%% Esercizio con metodo di bisezione
clc
clear
close all

p5 = @(x) x/8.*(63*x.^4 - 70*x.^2 + 15);
a = 0.6;
b = 1;
alphas = roots([63/8, 0, -70/8, 0, 15/8, 0]);
epsi = 10^-10;


plot(linspace(a,b), p5(linspace(a,b)))
grid on

i = 1;
err = 1;
while err > epsi
	mid = (a+b)/2;
	result = p5(a) * p5(mid);
	if result < 0
		b=mid;
	elseif result > 0
		a=mid;
	else
		disp('mid è radice');
		break;
	end

	e(i) = abs(alphas(4) - mid);			% Aggiungo un valore al vettore di errori
	i = i+1;
end

figure;
semilogy(e); %* Convergenza del metodo di bisezione
mid
pause;

%% Esercizio con Metodo di Newton
clc
clear
close all


f = @(x) exp(-x) - 10.^-9;
df = @(x) -exp(-x);
alpha = -log(10^-9)
plot(linspace(19, 21), f(linspace(19, 21)));

epsi1 = 10^-3;
epsi2 = 10^-2;

figure;
[approx1, itnum] = newton(0, f, df, epsi1, 100, false);
semilogy([1:itnum+1], abs(alpha - approx1), '-*');

figure;
[approx2, itnum] = newton(0, f, df, epsi2, 100, true);
semilogy([1:itnum+1], abs(alpha - approx2), '-*');