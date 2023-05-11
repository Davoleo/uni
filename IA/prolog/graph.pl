% Esempio di inclusione libreria
:- use_module(library(lists)).
% Quella delle liste è sempre inclusa automaticamente

% Dovrebbe essere un DAG

% Costruzione dell'operatore -> 
% - Infisso: A sinistra vuole un nodo, mentre a destra vuole un percorso o un nodo
% - Tipo: xfy
% - Indice di Precedenza: 450 [Al livello della precedenza degli operatori aritmetici]
% Docs Operatori di Default: https://swi-prolog.org/pldoc/man?section=operators
:- op(450, xfy, ==>).

node(a).
node(b).
node(c).
node(d).
node(e).
node(f).
node(g).
node(h).
node(i).
node(j).
node(k).
node(l).
node(m).

arc(a, b).
arc(a, c).
arc(b, c).
arc(c, e).
arc(c, f).
arc(c, i).
arc(d, e).
arc(d, f).
arc(d, g).
arc(e, j).
arc(f, l).
arc(f, m).
arc(g, l).
arc(g, m).
arc(h, i).
arc(h, k).
arc(i, e).
arc(i, j).
arc(i, k).

% Caso base, percorso vuoto?
% è davvero necessario? i percorsi che contengono archi vuoti sono di solito ridondanti.
% Quindi possiamo usare come caso base quello contenente un arco
path(X, Y, '==>'(X, Y)) :-
	arc(X, Y).

% Esiste un percorso tra X e un Y? , se esiste un Z raggiunto da un arco partendo da X e poi 
% da Z c'è un percorso che raggiunge Y
path(X, Y, X ==> P) :-
	arc(X, Z),
	path(Z, Y, P).

% Aggiungiamo un valore di composizione dei 2 nodi che hanno un arco tra di loro w(nodo1, nodo2)
% poi sostituito con l'operatore infisso ==> [Vedi definizione sopra]

% Nota: I linguaggi logici sono molto asciutti e si focalizzano molto sulla soluzione del
% Problema specifico e quindi nella realtà non sono quasi mai utilizzati da soli.

% Diversi problemi risolvibili con gli stessi predicati
% path (a, f). : verifica della presenza di un percorso
% path (f, X). : In quali nodi posso finire partendo da f?
% path (X, f). : Da quali nodi posso partire per arrivare a f?

% Nota: i parametri possono contenere variabili libere al contrario dei linguaggi imperativi.
