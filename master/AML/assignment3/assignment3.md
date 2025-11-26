# Modello
Il modello contiene 2 layer convoluzionali perché il dataset su cui si sta lavorando è molto semplice e le forme da imparare non sono complesse.

Per il primo layer si è deciso di utilizzare 10 filtri mentre 20 filtri per il secondo layer, per l'euristica di utilizzare meno filtri per individuare edge semplici all'interno dell'immagine e usare più filtri per la composizione di questi edge in forme più complesse come cerchi e linee; tuttavia per un dataset così semplice il cambiamento di questi layer non influenza significativamente l'accuratezza.

Da notare che il numero di filtri dell'ultimo layer convoluzionale influenzano molto di più il numero totale di parametri rispetto al primo siccome l'output di quel layer verrà appiattito e collegato al layer FC, tuttavia si è deciso di mantenere, il numero di filtri più alto nel primo layer per seguire l'euristica relativa alla complessità delle feature estratte.

Il dropout inserito serve per evitare di andare in overfitting, è stato scelto 0.2 come parametro in modo da non rimuovere troppe connessioni e quindi evitare overfitting mantenendo un buona velocità di apprendimento prima del plateau.

Le modifiche al numero di filtri sono state effettuate principalmente per restare entro il numero di parametri necessari per la consegna, cercando di spingere il più possibile l'allenamento, sempre evitando overfitting, per cercare di ottenere accuracy più alta possibile.

# Risultati

L'allenamento della rete riesce a svolgersi senza finire in overfitting ma arrivando ad un plateau che rispecchia la semplicità del problema da risolvere.

![learning_curves](./training.png)

Il modello offre prestazioni notevoli nonostante il basso numero di parametri: l'accuracy sul test set è di: 98.8%