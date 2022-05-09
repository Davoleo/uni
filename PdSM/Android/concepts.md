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