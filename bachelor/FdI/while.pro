% Tree structure 
is_tree(nil).

is_tree(X) :-
	atomic(X).

is_tree(L:R) :-
	is_tree(L),
	is_tree(R).


%% Expression semantics
eval(X, Sigma, Val) :-
	atom(X),
	!,
	store_read(Sigma, X, Val).

eval(cons(E1, E2), Sigma, Val) :-
	!,
	eval(E1, Sigma, Val1),
	eval(E2, Sigma, Val2),
	Val = Val1:Val2.

eval(E1 = E2, Sigma, Val) :-
	!,
	eval(E1, Sigma, Val1),
	eval(E2, Sigma, Val2),
	(Val1 = Val2 ->
		Val = nil:nil
	;
		Val = nil
	).

eval(tl(E), Sigma, Val) :-
	!,
	eval(E1, Sigma, ValE),
	(ValE = _T:C ->
		Val = C
	;
		Val = nil
	).

eval(hd(E), Sigma, Val) :-
	!,
	eval(E1, Sigma, ValE),
	(ValE = T:_C ->
		Val = T
	;
		Val = nil
	).

eval(D, _Sigma, D) :-
	assertion(is_tree(D)).


% Command semantics
transition(c(skip, Sigma), c(epsilon, Sigma)).

transition(c(X := E, Sigma), c(epsilon, Sigma1)) :-
	eval(E, Sigma, D),
	store_write(Sigma, X, D, Sigma1)

transition(c([C|Cs], Sigma), c(Cs, Sigma1)) :-
	transition(c(C, Sigma), c(epsilon, Sigma1)).

transition(c([], Sigma), c(epsilon, Sigma)).

transition(c(while(E, C), Sigma), Configuration) :-
	eval(E, Sigma, D),
	(D = nil ->
		Configuration = c(epsilon, Sigma)
	;	
		Configuration = c([C, while(E,C)], Sigma)
	).

transition(c(if(E, C1, C2), Sigma), Configuration) :-
	eval(E, Sigma, D),
	(D = nil ->
		Configuration = c(C2, Sigma)
	;
		Configuration = c(C1, Sigma)
	).

transition_star(c(C, Sigma), Configuration) :-
	(C = epsilon ->
		Configuration = c(C, Sigma)
	;
		transition(c(C, Sigma), Configuration_tmp)
		transition_star(Configuration_tmp, Configuration)
	).

% Program Semantics

split([Write], C, Write) :-
	!.

split([H|T], [HC, Write) :-
	!.

split(P, Read, C, Write) :- 
	P = [Read|Rest],
	assertion(Read = read(L)), is_var_list(L),
	split(Rest, C, Write).

sem(P) :- 
	P = [read(Input_List)|Rest]

% While Program
program(reverse, P) :-
	P = 
	[
		read([x]),
		y := nil,
		while(x, [
			y := cons(hd(x), y),
			x := tl(x)
		]),
		write(y)
	].