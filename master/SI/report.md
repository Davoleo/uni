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
Tuttavia è da notare che supporta un certo **schema URI**

# Proof of Concept



**porte dei server in utilizzo nella prova di concetto**:
- 8080 → Server vulnerabile che utilizza libreria Log4j
- 1380 → Proof of Concept in Python (LDAP server che ridireziona l'accesso all'Exploit)
- 8000 → webport server HTTP di base usato dal protocollo LDAP
- 9001 → socat per mettersi in ascolto sulla porta su cui verra eseguito reverse shell



