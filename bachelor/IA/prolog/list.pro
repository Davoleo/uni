% ? prima del tipo:
% + prima del tipo significa valore costante.

% member(?Term, ?List)
% True se il termine si unifica con un membro della lista
member(X, [X|_]).
member(X, [_|T]) :-
	member(X, T).
	
% append(?List1, ?List2, ?List3)
% True se la lista3 è il risultato di appendere la lista2 alla lista1
append([], X, X).
append([X|L1], L2, [X|L3]) :-
	append(L1, L2, L3).

% prefix(?List1, ?List2)
% Succeeds if List1 is a prefix of List2
prefix(X, Y) :-
	append(X, _, Y).

% reverse(+List1, ?Reversed)
% Succeeds if Reversed is the reversed list List
reverse(List, Rev) :-
	reverse(List, Rev, []).

reverse([], L, L).
reverse([H | T], L, SoFar) :-
	reverse(T, L, [H | SoFar])

% select(?Element, ?List1, ?List2)
% Succeeds if List2 is List less an occurrence of Element in List1
select(A, [A | B], B).
select(A, [B, C | D], [B | E]) :- 
	select(A, [C | D], E).


%% Predicato nonmember tramite cut e fail
nonmember(_, []).
nonmember(X, [X | _]) :-
	!,
	fail.
nonmember(X, [_ | R]) :-
	nonmember(X, R).

% Questa soluzione come tutte le soluzioni che coinvolgono la negazione ah dei comportamenti anomali in presenza di variabili libere. Ad esempio:
:- nonmember(R, [a, b, c]).  % false
:- nonmember(z, [a, b, R]).  % false