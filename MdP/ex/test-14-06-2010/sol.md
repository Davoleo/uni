### Ex 3
- Viola l'OCP (Open-Closed Principle), questo dice in linea di massima la struttura delle astrazioni di un progetto dovrebbe essere aperto verso l'estensione ma chiuso verso la modifica
- Seguire questo principio permette una migliore manutenzione del codice in quanto per aggiungere nuove funzionalità non serve andare a modificare il contenuto base, o altre funzionalità
- Il codice nel testo dell'esercizio non è estendibile facilmente ma solo tramite modifica della funzionalità di base che a sua volta gestisce tutti i casi possibili senza lasciare spazio a possibili aggiunte future
- Una soluzione alternativa è definire le varie espressioni: Var, Const, Add, Sub, etc... come sottoclassi della classe base Expr e quindi lasciare la possibilità di estendere il repertorio di espressioni senza dover modificare la classe Expr

