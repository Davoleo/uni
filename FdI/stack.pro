% Empty List
% [].
% List of 3 elements
% [a, b, c].


% Access the first element
member(X, [X|_]).
member(X, [_|T]) :- member(X, T).

stack_is_empty(-Stack_out)
% Create empty stack
stack_empty([]).

stack_is_empty(+Stack_in)
% Returns whether the stack is empty
stack_is_empty([]).

/* stack_push(+New_element, +Stack_in, -Stack_out) */
stack_push(X, Stack_in, Stack_out) :-
	Stack_out = [X|Stack_in].

/* stack_pop(+stack_in, -Element_on_top, -Stack_out) */
stack_pop([], _X, _Stack_out) :-
	writeln('error: empty stack'),
	halt.

stack_pop([X|Stack_out], X, Stack_out).