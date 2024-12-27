% Interprete online: https://swish.swi-prolog.org/

% Clausola con un fatto di arità 1
p(a).
p(c).

% Clausola con un fatto di arità 2
p(a, b).

q(a).
% La prima a viene dal fatto della linea 8 mentre
% la seconda deriva dal fatto alla linea 2
q(X) :- p(X).

% is: valuta l'espressione aritmetica destra [atomi e variabili con un valore] 
% e controlla se è uguale alla var a sinistra
% is è un operatore extra-logico: asimmetrico
% X is 1 + 3

% Calcolo del fattoriale
fact(0, 1).
fact(N, F) :- 
    N > 0, % Extra-Logico
	M is N - 1,
	fact(M, G),
	F is N * G.
% Extra in Prolog se la chiamata ricorsiva è l'ultima si può riutilizzare
% il frame nella ricorsione il che permette di avere stack di "dimensione arbitraria"
% In questo caso a causa degli operatori extra-logici c'è questo tipo di limitazione/problema

guess_num :- loop(start).

loop(15) :-
	write('You Guessed it!').

loop(X) :-
	X \= 15,
	write('Guess Number'),
	read(Guess),
	write(Guess),
	write(' is not the number'), nl,
	loop(Guess).