### Ex 3
- Viola l'OCP (Open-Closed Principle), questo dice in linea di massima la struttura delle astrazioni di un progetto dovrebbe essere aperto verso l'estensione ma chiuso verso la modifica
- Seguire questo principio permette una migliore manutenzione del codice in quanto per aggiungere nuove funzionalità non serve andare a modificare il contenuto base, o altre funzionalità
- Il codice nel testo dell'esercizio non è estendibile facilmente ma solo tramite modifica della funzionalità di base che a sua volta gestisce tutti i casi possibili senza lasciare spazio a possibili aggiunte future
- Una soluzione alternativa è definire le varie espressioni: Var, Const, Add, Sub, etc... come sottoclassi della classe base Expr e quindi lasciare la possibilità di estendere il repertorio di espressioni senza dover modificare la classe Expr

### Ex 4
- Se la parola "inizio" non è prima di fine i 2 iteratori non saranno mai nella stessa posizione e quindi si va in ciclo infinito, e in undefined behaviour quando si dereferenzia 
- Nella funzione g si va in undefined behaviour perché insert non può sovrascrivere celle già riempite [unless il vettore è allocato e vuoto]
  - Per evitare errori con l'insert si può direttamente sostituire con dereferenziazione e assegnazione di un const char*