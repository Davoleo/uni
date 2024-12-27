## Moduli
- Platform
- GUIs
- Location and Mapping
- Data Persistence
- Async Tasks, Thread and Handlers
- Services
- Networking
- TBD (Bluetooth, Photo/Video)

# Android Jetpack
- Collezione di Componenti di Software android per migliorare e rendere facile sviluppo di app Android
- Questi componenti aiutano a
  - Seguire Best Practices
  - Liberarsi dalla scrittura di codice boilerplate
  - Semplificare attività complesse, in modo che ci si possa concentrare sul codice che interessa 
- Packages: `androidx.*`

### La piattaforma
- Suite Software composta di: OS, Applicazioni, e middleware
- La base è il sistema operativo Linux
- HAL: Hardware Abstraction Layer tra l'hardware visico e lo stack software Android
- Il Kernel gestisce:
  - Sicurezza
  - Gestione con Low-level Energy 
  - Gestione di Threading e Processi
  - Networking
  - Display, keypad input, camera, flash memory, audio

### Kotlin
- Linguaggio ufficiale per Android
- è compilato staticamente, viene eseguito sulla JVM e può anche essere compilato a Javascript tramite la LLVM compiler infrastructure
- Espressivo, conciso e potente
- Interoperabile con android e i suoi altri linguaggi/runtime

### Dalvik Virtual Machine
- Basata sulla JVM ma ottimizzata per dispositivi mobili
- Small memory footprint, più istanze della Dalvik VM possono essere eseguite sul device
- I programmi sono scrtti in un dialetto di java e compilati in bytecode, poi vengono convertiti da .class compatibili con JVM a Dalvik-compatible (.dex)
- Ogni applicazione Android viene eseguita nel suo processo con la sua istanza della DVM
- C'è garbage collection

### Application Sandbox
- Creazione di un nuovo utente per ogni application vendor. Ogni applicazione è eseguita con diversi privilegi utente (eccetto quelle firmate dallo stesso vendor)
- I file di un applicazione di default sono inaccessibili dalle altre
- l'SDK offre ContentProvider e Intent per permettere alle applicazioni di comunicare e scambiare dati
- La soluzione -> mantenere alta sicurezza in un mondo di diversi piccoli third party vendors

### Security e Permessi
- Android utilizza diverse misure di sicurezza e integrita per assicurare i dati dell'utente e che il device non sia vulnerabile a malware
- Ogni utente è un utente con specifici permessi, limitati, ad hoc
- Application Permissions
  - Ogni applicazione registra specifici privilegi di accedere a risorse condivise; Alcuni privilegi sono ad esempio phone functionalities, network, file system, camera
  - Permessi in più sono necessari per privilegi come: user contacts o la location
- Application Signing
  - Tutte le applicazioni devono essere certificate e firmate con la propria chiave privata da sviluppatore
  - Permette di verificare l'integrità dell'applicazione
  - I certificati di development possono essere usati in development ma non per pubblicare app sullo store

### Differenze con Traditional Java
- Nelle applicazioni andrdoid ci possono essere diversi entry point a seconda di come viene aperta l'app
- I diversi componenti
  - Activities
  - Services
  - Content Providers
  - Broadcast Receivers

## Activities
- Unità di esecuzione del codice e unità di interazione dell'app con l'utente
- Per creare un attività bisogna sottoclassare Activity (o altre sue sottoclassi)
- Diverse activity sono organizzate in una struttura a stack, dove i nuovi elementi possono essere posizionati a seconda delle azioni degli utenti
- Possono anche esserci activity che provengono da app diverse lungo lo stack
- In situazioni di scarsità di risorse, le activity che si trovano in basso nello stack potrebbero essere distrutte dal sistema operativo
- **Lifecycle**
  - `onCreate()`: Chiamato quando l'activity viene creata all'inizio
  - `onRestart()`: Chiamato dopo che l'attività è stata fermata, appena prima che venga riavviata
  - `onStart()`: Chiamato appena prima che l'activity diventi visibile all'utente
  - `onResume()`: Un attimo prima che l'activity possa iniziare a interagire con l'utente (quando è nel top dell'activity stack)
  - `onPause()`: Chiamato quando il sistema sta per resumere un altra activity. Questo metodo è utilizzato di solito per fare cmabiamenti a dati persistenti, bloccare animazioni e qualsiasi cosa che consuma CPU. Deve essere fatto velocemente perché altrimenti la ripresa della prossima activity viene rallentata
  - `onStop()`: Chiamato quando l'activity non è più visibile con l'utente. Questo potrebbe essere chiamato perché sta per essere distrutta oppure perché un'altra activity la sta coprendo
  - `onDestroy()`: chiamato appena prima che l'activity venga distrutta. Chiamata finale, chiamata perché l'activity sta per finire oppure perché il sistema la sta distruggendo temporaneamente per liberare risorse
- **Salvare Stato Activity**
  - Quando il sistema distrugge un activity per recuperare memoria 
  - Metodi extra `onRestoreInstanceState()`, `onSaveInstanceState()` permettono all'activity di essere salvata e restorata

## Services
- Classe per operazioni di background che sono attive ma non sono visibili per l'utente.
- Operazioni lunghe che non devono interagire con utente: chat, HTTP fetcher, GPS location
- Lifecycle più semplice delle activity
- Inoltre un servizio può essere collegato ad un certo client tramite IPC
- 2 Tipi: Unbounded e Bound
  1. Lifecycle: `startService()` -> `onCreate()` -> `onStartCommand()` -> Servizio Running -> `onDestroy()` -> Service Shutdown
  2. Lifecycle: `bindService()` -> `onCreate()` -> `onBind()` -> Client collegati al servizio -> `onUnbind()` -> `onDestroy()` -> Service Shutdown 

## Content Provider
- Accesso a Set di dati strutturati (e.g. File o Database)
- Incapsulamento di dati, e offre sicurezza 
- Altre applicazioni possono accedere alle informazioni di un content provider attraverso un URI specifico: `content://`
- Operazioni tipiche: Create [Insert], Read [Query], Update, Delete
- L'OS android offre dei ContentProvider di default per Browser, Contatti, Calendario, etc.

## Intents
- Sono messaggi asincroni che i componenti possono generare e inviare ad altri componenti in esecuzione
- non vengono mandati direttamente  ma, sono mandati al sistema android il quale esegue _receiver determination_ e determina cosa fare 
- Un intent può anche contenere dati. Questi dati possono essere usati per 
- Android supporta Intent Explicit e Implicit
  - Esplicito: quando lo si genera si sa direttamente chi lo gestirà
  - Implicito: Il sistema decide come trattarlo
  
## Broadcast Receiver
- Endpoint di ricezione degli Intent: rappresentano una variante di comunicazione tra diversi processi basata su oggetti di tipo Intent
- Non è obbligato ad essere un'activity
- Potrebbe decidere di mostrare notifiche sulla status bar
- Gateway di Accesso ad altre componenti (intended to do minimal work)

### Android Application Context
- Il context è entità centrale e accessibile da tutte le app, e contiene informazioni globali di un applicazione e dell'ambiente
- Clase astratta di AdroidOS
- Feature:
  - Risorse dell'applicazione, immagini, suoni, asset
  - Accedere a preferenze applicazioni
  - Lanciare Activity
  - Richiedere servizi di sistema (e.g. Location Service)
  - Gestire file, directory, database privati di applicazioni

### Android Application Manifest
- Manifesto XML con nome `AndroidManifest.xml`
- Vengono dichiarate activity, service, content providers, Broadcast receiver, Permessi, nome app, SDK requirements
- I file di Manifesto sono condivisi con il sistema operativo per fare in modo che l'applicazione venga caricata correttamente

### R Object
- Le risorse di un app sono indicizzate e assegnate ad un identificatore unico a cui si può accedere tramite la classe automaticamente generata chiamata R
- Consente di avere accesso rapido tramite filename
- Ottenimento dell'istanza di una risorsa tramite `Context.getResources()`

### Application Logs
- Il framework offre un metodo strutturato per loggare roba nell'output console
- La classe di Log offre 5 metodi statici:
  - `Log.v(TAG, <log>)` //VERBOSE
  - `Log.d(TAG, <log>)` //DEBUG
  - `Log.i(TAG, <log>)` //INFO
  - `Log.w(TAG, <log>)` //WARNING
  - `Log.e(TAG, <log>)` //ERROR
- DEBUG logs sono compilati ma strippati a runtime
- un buon approccio è creare un TAG per la propria classe che marca i log della classe in questione

### Model View Controller
- Pattern architetturale per isolare la UI dalla logica dell'applicazione
- MVC permette facile sviluppo, testing, e mantenimento di diversi componenti
- **Model**: Dati dell'applicazione
- **View**: Rappresentazione del modello Mediata dal Controller (organizzate in struttura gerarchica)
- **Controller**: Mediatore tra la view e i dati che il controller governa (implementato come una coda di eventi di interazioni utente)

### Android User Interface
- Si basa su **View** (componenti atomiche -> singoli widget) e **ViewGroup** objects (basate su layout di più oggetti)
- **Gerarchia**
  - Albero di View e ViewGroups (Gli oggetti View sono le foglie dell'albero)
  - `setContentView()` permette di impostare un layout ad una View
  - I componenti sono disegnati tramtie una visita in-order dell'albero

## Layout
- File XML all'interno del progetto
- Definisce una gerarchia di viste
- Esistono diversi tipi di View groups chiamati layout per raggruppare viste
  - LineareLayout
  - RelativeLayout
  - TableLayout
  - ...
- **Layout Attributes**
  - Gli attributi XML possono essere generici per la View oppure specifici per un controllo
- **ID Attribute**
  - Una resource che ha un attribute id può essere unicamente identificato nell'albero e nel codice Java
  - è accesibile tramite `context.findViewById(R.id.<resource_id>)`
  - una '@' all'inizio della della stringa indica che il parser XML deve espandere il resto della ID string e identificarla come una risorsa id
  - il simbolo '+' significa che è una nuova risorsa e deve essere generata nel file `R.java`

## Widget
- 2 Scopi
  1. mostrare qualcosa all'utente 
  2. Dare modo all'utente di interagire 
- Ci sono componenti semplici, complessi, e si possono anche creare componenti custom

## Activity
- Activity -> elemento centrale delle app Adnroid
- è Associata con:
  - Vista 
    - Recupero di riferimenti alle viste
    - Gestione di eventi che provengono dalle viste
  - Modello
    - Leggere dati dalla struttura del modello
    - Scrivere dati nell'app storage in accordo con la struttura del modello
- Si può fare l'override di metodi legati al lifecycle dell'activity, tra i quali il più comune: `onCreate()`

### Input Events
- Interfaccia che deve essere implementata per ricevere gli eventi che arrivano dalla View

### Lanciare Activity
- `startActivity(Intent, activityClass)` 
- `startActivityForResult(Intent, int)` l'int serve per collegare la richiesta alla risposta dell'activity quando finirà
  - Quando l'activity termina viene invocato il metodo: `onActivityResult(int, int, Intent)`
  - Bisogna fare `setResult()` sull'activity per settare il risultato che verrà acchiappato da onActivityResult
- `finish();` per terminare un'activity


### Principi di Design ufficiali
- **Keep it brief**: "Use short phrases with simple words"
- **Pictures are faster than words**: "Consider using pictures to explain ideas. 
They get people's attention and can be much more efficient than words."
- **Decide for me but let me have the final say**: Take your best guess and act rather than asking first. Too many choices and decisions make
people unhappy. Just in case you get it wrong, allow for 'undo'"
- **Only show what I need when I need it**: "People get overwhelmed when they see too much at once. Break Tasks and information into small chunks.
Hide options that aren't essential at the moment, and teach people as they go.
- **I should always know where I am**: "Give people confidence that they know their way around. Make places in your app look distinct and use
transitions to show relationships among screens. Provide feedback on tasks in progress."
- **If it looks the same it should act the same**: "Avoid modes, which are places that look similar but act differently on the same input."
- **It's not my fault**: "Be gentle in how you prompt people to make corrections. They want to feel smart when they use your app. If something goes wrong, give clear recovery instructions but spare them the technical details. If you can fix it behind the scenes, even better"
- **Make important things fast**: "Not all actions are equal. Decide what's most important in your app and make it easy to find and fast to use."
- **Do not reinvent the wheel!**: "You're not alone! At any given moment, somewhere in the world someone faces the same software/design problems. 
You know you don't want to reinvent the wheel (or flat tire), so look around and focus on relevant aspects for your application!
- **Use native components and themes**: "A rich and complete Mobile platform like Android provides many useful, tested, and well-known native components. You should use them during design and development phases.
- **Get inspired! Sometimes copying is ok**: "Look around and learn from existing applications! If you don't know how to design your app or a specific section, have a look at well known and official applications in order to understand how they are designed and composed"
- **Use online free tools & resources**: "If you are not a designed, rely on existing tools and resources to improve and simplify the UI of your application. Keep it simple and clear.