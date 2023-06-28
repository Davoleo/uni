:- use_module(library(dif)).

nevermember(_, []).
nevermember(X, [H|R]) :-
	dif(X, H),
	nevermember(X, R).

% Il vincolo di dif viene riverificato ogni volta che si cambia la variabile
% nevermember(X, [1,2,3]), X=2.
% Quindi viene comunque risultato false.

% Essendo un vincolo dif può essere espresso anche prima che le varie variabili siano assegnate
