:- use_module(library(clpfd)).

% Per ogni vincolo aggiungo nel goal viene effettuata una post 
% e viene propagata la modifica dei vincoli, 
% fin quando si arriva all'ultimo vincolo che svuota almeno uno dei 2 dominis
% X #> Y, X in 1..5, X + Y #= 10.

% label 
% - Primo argomento una lista di variabili da sostituire nell'ordine 
%	in cui vogliamo che siano sostituite
% X #> Y, X in 1..5, X #\= 3, label([X]).

% Esempio non lineare
% X * X -4 #=< 0.
-X * X +4 #>= 0.

% SEND MORE MONEY problem with CLPFD
send(Vars) :-
	Vars = [S,E,N,D,M,O,R,Y],
	Vars ins 0..9,
	M #\= 0, S #\= 0,
	all_distinct(Vars),
	S*1000 + E*100 + N*10 + D + 
	M*1000 + O*100 + R*10 + E #=
	M+10000 + O*1000 + N*100 + E*10 + Y,
	label(Vars).


% NQueens problem.
queens(N, Queens) :-
	length(Queens, N),
	Queens ins 1..N,
	safe_queens(Queens),
	label(Queens).

safe_queens([]).
safe_queens([Queen | QueenRest]) :-
	safe_queens(QueenRest, Queen, 1),
	safe_queens(QueenRest).

safe_queens([], _, _).
safe_queens([Queen | QueenRest], Queen0, D0) :-
	Queen0 #\= Queen,
	abs(Queen0 - Queen) #\= D0,
	D1 #= D0 + 1,
	safe_queens(QueenRest, Queen0, D1).
