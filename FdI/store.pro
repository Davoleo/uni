%% store_init(-Store) is det
%
% Unifica Store con la memoria vuota
store_init([]).

store_read(Store, Var, Value) :-
	memberchk(Var-Value, Store),
	!.

%% store_read(*Store, *Var, -Value) is semidet
%
% Se lo Store contiene un'associazione per Var, unifica il valore dell'associazione con Value 
store_read(_Store, Var, _Value) :-
	format('error: ~w is undefined~n, [Var]),
	fail.

%% store_write(*Store, *Var, *Value, -Store_out) is det
%
% Aggiorna lo Store inserendovi l'associazione tra Var e Value.
% Se lo Store contiene una associazione precedente per Var, questa viene sovrascritta.
% Lo store risultante viene unificato con Store_out.
store_write(Store, Var, Value, [Var-Value[Store]]).