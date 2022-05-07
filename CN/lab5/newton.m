function [approx, num_iter] = newton(x0, fun, deriv_fun, threshold, max_iter, criterion_increment)
	% Calcola una successione di approssimanti alle radici delle equazioni tramite il metodo di newton
	% threshold è la tolleranza oltre alla quale l'algoritmo si arresta
	% max_iter è il numero massimo di iterazioni possibili prima dell'arresto finale

	x = x0;
	approx = [x];
	num_iter = 0;

	stop_criteria = 1;

	while num_iter < max_iter && stop_criteria > threshold
		num_iter = num_iter + 1;
		x_next = x - (fun(x)/deriv_fun(x));
		approx = [approx; x_next];
		if criterion_increment == true
			stop_criteria = abs(x_next - x);	% Criterio dell'incremento
		else
			stop_criteria = abs(fun(x_next));	% Criterio del residuo
		end
		x = x_next;
	end

end