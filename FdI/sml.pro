% Stack machine (linear)

execute(N, PC, Stack_in, Register_File_in, PC, Stack_out, Register_File_out) :-
	integer(N), !,
	stack_push(N, Stack_in, Stack_out),
	Register_File_out = Register_File_in.
execute(+, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, X, Stack_tmp1),
	stack_pop(Stack_tmp1, Y, Stack_tmp2),
	R is X + Y,
	stack_push(R, Stack_tmp2, Stack_out),
	Register_File_out = Register_File_in.

execute(-, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, X, Stack_tmp1),
	stack_pop(Stack_tmp1, Y, Stack_tmp2),
	R is Y - X,
	stack_push(R, Stack_tmp2, Stack_out),
	Register_File_out = Register_File_in.

execute(*, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, X, Stack_tmp1),
	stack_pop(Stack_tmp1, Y, Stack_tmp2),
	R is X * Y,
	stack_push(R, Stack_tmp2, Stack_out),
	Register_File_out = Register_File_in.

execute(/, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, X, Stack_tmp1),
	stack_pop(Stack_tmp1, Y, Stack_tmp2),
	R is Y // X,
	stack_push(R, Stack_tmp2, Stack_out),
	Register_File_out = Register_File_in.

execute(mod, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, X, Stack_tmp1),
	stack_pop(Stack_tmp1, Y, Stack_tmp2),
	R is Y mod X,
	stack_push(R, Stack_tmp2, Stack_out),
	Register_File_out = Register_File_in.

execute(swap, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, X, Stack_tmp1),
	stack_pop(Stack_tmp1, Y, Stack_tmp2),
	stack_push(X, Stack_tmp2, Stack_tmp3),
	stack_push(Y, Stack_tmp3, Stack_out),
	Register_File_out = Register_File_in.

execute(dup, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, X, Stack_tmp1),
	stack_push(Stack_tmp1, X, Stack_tmp2),
	stack_push(Stack_tmp2, X, Stack_out),
	Register_File_out = Register_File_in.

execute(read, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	read(N),
	stack_push(X, Stack_in, Stack_out),
	Register_File_out = Register_File_in.

execute(fetch, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, Index, Stack_tmp1),
	register_file_read(Index, Register_File_in, Value),
	stack_push(Value, Stack_tmp1, Stack_out),
	Register_File_out = Register_File_in.

execute(store, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, Index, Stack_tmp1),
	stack_pop(Stack_tmp1, Value, Stack_out),
	register_file_write(Index, Register_File_in, Value, Register_File_out).

interpret(Code) :-
	PC_in = 0,
	stack_empty(Stack_in),
	register_file_init(Register_File_in),
	interpret_loop(Code, PC_in, Stack_in, Register_File_in, _PC_out, Stack_out, _Register_File_out),
	(stack_is_empty(Stack_out) -> 
		true
		;
		writln('warning: non-empty stack at the end of computation')
	).

execute(print, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, X, Stack_out),
	write(X)
	Register_File_out = Register_File_in.

execute(println, PC, Stack_in, Register_File_in, PC, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, X, Stack_out),
	writeln(X)
	Register_File_out = Register_File_in.

execute(jump, PC_in, Stack_in, Register_File_in, PC_out, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, Offset, Stack_out),
	PC_out is PC_in + Offset,
	Register_File_out = Register_File_in.

execute(jump, PC_in, Stack_in, Register_File_in, PC_out, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, Offset, Stack_out),
	PC_out is PC_in + Offset - 1,
	Register_File_out = Register_File_in.

execute(jumpz, PC_in, Stack_in, Register_File_in, PC_out, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, Offset, Stack_tmp),
	stack_pop(Stack_tmp, Value, Stack_out),
	(Value =:= 0 ->
		PC_out is PC_in + Offset - 1,
		;
		PC_out = PC_in
	),
	Register_File_out = Register_File_in.

execute(jumpz, PC_in, Stack_in, Register_File_in, PC_out, Stack_in, Register_File_in,) :-
	stack_pop(Stack_in, Offset, Stack_tmp),
	stack_pop(Stack_tmp, Value, Stack_out),
	(Value =\= 0 ->
		PC_out is PC_in + Offset - 1,
		;
		PC_out = PC_in
	),
	Register_File_out = Register_File_in.

interpret_loop(Code, PC_in Stack_in, Register_File_in, PC_out, Stack_out, Register_File_out).
interpret_loop(Code, Stack_in, Register_File_in, Stack_out, _Register_File_out) :-
	nth0(PC_in, Code, Instruction),
	Instruction = halt -> Stack_out = Stack_in, Register_File_out = Register_File_in; PC_tmp1 is PC_in + 1,
	execute(Instruction, PC_tmp1, Stack_in, Register_File_in, PC_tmp2, Stack_tmp, Register_File_tmp),
	interpret_loop(Code, PC_tmp2, Stack_tmp, Register_File_tmp, PC_out, Stack_out, Register_File_out).

% X * Y
test1 :- 
	P = [read, read, * print],
	interpret(P).

% X^2
test2 :- 
	P = [read, dup, * print],
	interpret(P).

% X + X^2
test3 :- 
	P = [read, dup, 1, store, dup, *, 2, store, 1, fetch, 2, fetch, +, println],
	interpret(P).


