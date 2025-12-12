### Preprocessing aggiuntivo sui dati
Il libro su cui si è deciso di allenare il modello neurale è Frankenstein di Mary Wollstonecraft Shelley, in lingua inglese originale.

è stato deciso di tagliare la parte iniziale del testo (primi 1400~ caratteeri) contenenti l'introduzione del libro e l'indice dei capitoli.

### Accuracy sul test set (CNN)
Il modello CNN (399,042 parametri) costruito in laboratorio mostra un'accuracy sul test set del 29.24%.
Questo rispecchia il fatto che la CNN tratta i dati da elaborare in modo inottimale, siccome invece di gestire le matrici in input come un elenco di caratteri in one-hot encoding, esse vengono interpretate come matrici sparse di 1 e 0 direttamente e vengono analizzate in sotto-regioni quadrate corrispondenti ai filtri dei layer convoluzionali.

### Modello LSTM
Il modello LSTM provato è un modello a singolo layer con **256** unità. Il numero di unità nel layer è stato scelto per avere un quantitativo totale di parametri simile alla rete CNN creata durante il laboratorio (347,714 parametri).
Inizialmente sono stati testati 2 layer LSTM nel modello, tuttavia non portavano miglioramenti significativi, senza contare lo svantaggio di aumentare l'overfitting sul training set.

Il layer finale invece è fully connected con `softmax` come funzione di attivazione, il layer ha lunghezza pari al numero di caratteri diversi esistenti nel libro, per ottenere come output una distribuzione di probabilità relativa al successivo carattere più probabile.
Come **ottimizzatore** si sono notati risultati migliori (+2%~) con `Adam` piuttosto che `RMSProp` per lo stesso quantitativo di epoche (convergenza più veloce).

E' stato aggiunto anche del dropout al'interno delle unità LSTM per evitare overfitting: più precisamente `dropout=0.2` e `recurrent_dropout=0.2`, questi parametri corrispondono rispettivamente al dropout all'output del layer LSTM e tra gli stati nascosti interni alle unità LSTM. E' stato invece evitata `BatchNormalization` in quanto introduceva parecchio overfitting nel modello senza migliorare l'accuratezza sul test set significativamente.

### Risultati (RNN)
Con gli iperparametri scelti il modello ottiene una buona prestazione di 54.40% di accuracy sul training set e di **54.08%** di accuracy sul _test set_, si può notare l'assenza totale di overfitting grazie alla presenza di dropout.