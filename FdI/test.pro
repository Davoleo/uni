% identificatore che iniziano con la maiuscola -> Variabili
% identificatore che iniziano con la minuscola -> Costanti
% I parametri nelle funzioni possono essere usati sia con input sia come output

% induzione sull'essere naturali
is_natural(z) :- true. 
is_natural(s(X)) :- is_natural(X).

% add(Addendo1, Addendo2, risultato)
% se true è implcito
add(z, Y, Y).
add(s(X), Y, s(Z)) :- add(X, Y, Z);

mul(z, Y, z);
mul(s(X), Y, Z) :- mul(X, Y, XY), add(XY, Y, Z).