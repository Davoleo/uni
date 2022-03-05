### Alcune Keyword dell'OBjective-C
- `id` = Puntatore ad un oggetto di qualsiasi tipo (simile a void* in C)
- `nil` = puntatore che punta a niente (NULL in C)
- `BOOL` = tipo definito (tramite typdef in objc.h) per boolean values
  - `YES == 1` (true)
  - `NO == 0` (false)
- `self` = puntatore all'oggetto corrente (uguale a 'this' in java)

### Memory management
- in objective-C tutti gli oggetti sono allocati dinamicamente sull'heap (motivo per cui si usano SEMPRE i pointer per utilizzare oggetti)
- Ci sono 2 aree in cui la memoria è controllata: stack and heap
- Nello stack:
  - lo stack è un area di memoria con politica FIFO
  - Local (function) variables storage
  - Invocation record: tiene informazioni su tutte le variabili
- Nell'heap:
  - ritorno di una zona di memoria casuale nell'heap della size specificata
  - Esempio:
  ```c
  char* cstr = malloc(sizeof(char)*6);
  for (int i = 0; i < 5; i++)
  	cstr[i] = ('a' + i);
  cstr[5] = '\0';
  printf("%s", cstr);
  //Chiamata di restituzione di memoria
  free(cstr);
  ```
  - java usa un garbage collector per automatizzare la restituzione della memoria
  - In objective-c si usa una tecnica chiamata: **reference counting**
    1. si mantiene un conto di nel numero di volte che si punta ad un oggetto
	2. quando si ha bisogno di una reference ad un oggetto si incrementa il count
	3. quando si ha finito di lavorare con l'oggetto si diminuisce il count
	4. quando il contatore arriva a 0 la memoria è liberata (<ins>accedere all'oggetto freeato -> crash dell'app</ins>) il metodo `dealloc` di NSObject è chiamato automaticamente (va implementato nel caso di oggetti che devono essere liberati)
- Per restituire memoria allocata dinamicamente in C e C++ si usa `free()` e `delete`


#### Manual Reference Counting
- un oggetto ritornato da **alloc/init** ha un reference count di 1
- NSObject definisce 2 metodi per incrementare e decrementare il reference count:
  - **retain**: increase by 1
  - **release**: decrease by 1
- Metodo `retainCount` ritorna il reference count per l'oggetto su cui è effettuata la chiamata
- modello: **Object ownership**
  - Ogni oggetto rimane in vita finché c'è almeno un proprietario
  - Per diventare un proprietario di un oggetto o lo si alloca oppure si chiama retain
  - release per fare in modo di non essere più proprietario -> 0 proprietari -> deallocazione
- **Temporary object ownership**
  - Ci sono volte in cui mandare un release potrebbe creare una deallocazione prematura
  - Molte classi danno sia l'opzione di creare oggetti da gestire manualmente, ma anche oggetti autorilascianti

#### Automatic Reference Counting
- Da iOS 4 c'è l'ARC, il compilatore analizza il codice e aggiunge automaticamente l'increment e il decrement o l'autorelease as needed
- l'ARC NON è un Garbage Collector -> non c'è un processo in esecuzione in memoria
- Meno codice -> meno rischio
- in Progetti che usano ARC l'uso dei metodi di Manual Reference Counting è proibito
- Non c'è nemmeno da implementare dealloc (lo fa automaticamente l'ARC)
- Introduzione del concetto delle **Weak e Strong references**
  - strong -> Diventiamo proprietari dell'oggetto a cui ci riferiamo 
    - una property strong è equivalente a retain ma strong ha accezione ARC, mentre retain ha accezione MRC
  - weak -> Non diventiamo proprietari dell'oggetto a cui ci riferiamo (e.g. l'oggetto potrebbe essere rilasciato senza che noi lo sappiamo)
    - una property weak per l'ARC il puntatore diventa nil se l'oggetto di cui non sono proprietario viene freeato, mentre nel caso dell'assign per l'MRC non viene cambiato il valore del puntatore.


### Protocols
- Contenitori di liste di metodi (akin alle interfacce in java)
- Definisce un modo per accedere ad un oggetto in base a quello che sa fare
- _Protocols define messaging contracts_: un oggetto sa rispondere a certi messaggi
- è diverso dall'ereditarietà in quanto si possono vedere oggetti come tipi di oggetti che fanno certe azioni più che facenti parte di una certa gerarchia di classi
- Una classe che si può definire conforme ad un protocollo se definisce tutti i metodi @required e eventualmente i metodi @optional

### Categories
- Aumentare le funzionalità della classe utili in certe situazioni particolari
- Estendere una classe è un approccio molto complesso oppure non fattibile.
- le Categories aggiungono metodi a classi esistenti senza creare sottoclassi

### Method Invocation
- La Method invocation è basata su message passing agli oggetti
- Il message passing è diverso dai metodi classici di invocazione perché il metodo eseguito non è legato ad una specifica sezione di codice: Il target è risolto dinamicamente a runtime
- Se il ricevitore di un messaggio non risponde -> un eccezione è lanciata
  - Motivo per cui bisogna essere sicuri che l'oggetto risponda utilizzando introspection (ispezionare oggetto prima di chiamare il metodo guardando se lo sa gestire) § Metodi di introspezione:
    - isKindOfClass: can be used to check if the object's type matches a class o una dei suoi subclasses
    - isMemberOfClass: usato per controllare se il tipo di oggetto 	matcha una cerca classe strettamente
    - respondsToSelector: utilizzato per controllare se un oggetto può rispondere ad un certo messaggio e casting pointers per forzare la chiamata di un certo metodo
- è possibile mandare un messaggio a nil: 0 è ritornato

### Object creation:
1. Allocazione di Memoria
2. Istanziazione e inizializzazione dell'oggetto
- L'allocazione è fatta usando il metodo `alloc` di `NSObject`
  - chiede all'OS di allocare una quantità di memoria sufficiente per l'oggetto
  - Ereditato da `NSObject`
  - Fa in modo di impostare tutti campi dell'oggetto a `nil`
- L'inizializzazione avviene attraverso un metodo che inizia con `init` (prefisso)
- Esempio Creazione di un Oggetto
```mm
MDPoi* poi = [[MDPoi alloc] initWithName:@"MyPoi" latitude:45.2 longitude: 10.12];
```


Tutte le variabili d'istanza sono settate propriamente tramite un **initializer** method
- Il nome dell'initializer inizia con `init`
- Ogni classe ha il suo inizializzatore progettato
- ogni inizializzatore deve prima invocare l'inizializzatore della superclasse e controllare che non abbia ritornato un oggetto `nil`
- Si possono avere più di un initializer ma ognuno deve chiamare quello designated

