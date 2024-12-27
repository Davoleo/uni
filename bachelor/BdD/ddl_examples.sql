--Nazioni(nome)
CREATE TABLE Nazioni(
    nome VARCHAR(100) NOT NULL,
    PRIMARY KEY (nome)
);

--Edizioni(anno, nazione ospitante, nazione vincitrice)
CREATE TABLE Edizioni (
    anno NUMERIC(4) NOT NULL,
    nazione_ospitante VARCHAR(100) NOT NULL,
    nazione_vincitrice VARCHAR(100), -- nullable
    PRIMARY KEY (anno),
    FOREIGN KEY (nazione_ospitante) REFERENCES Nazioni(nome)
    FOREIGN KEY (nazione_vincitrice) REFERENCES Nazioni(nome)
)

--squadre()
CREATE TABLE Squadre (
    edizione NUMERIC(4) NOT NULL,
    nazione VARCHAR(100) NOT NULL,
    cognome_nome_allenatore VARCHAR(100)
)
--modifica dello schema della tabella
ALTER TABLE Squadre
    ADD CONSTRAINT SQUADRE_KEY PRIMARY KEY (edizione, nazione);
ALTER TABLE Squadre
    ADD CONSTRAINT SQUADRE_edizione_FKEY 
    FOREIGN KEY (edizione) REFERENCES Edizioni(anno);
ALTER TABLE Squadre
    ADD CONSTRAINT SQUADRE_nazione_FKEY 
    FOREIGN KEY (nazione) REFERENCES Nazioni(nome);
ALTER TABLE Squadre 
    ALTER COLUMN cognome_nome_allenatore SET NOT NULL;

-- NUOVA SIGLA CIFC: CODE IS FUCKING CODE (@Zambo-dev)

--Giocatori(id, cognome nome, anno nascita)
CREATE TABLE Giocatori(
    id NUMERIC(10) NOT NULL PRIMARY KEY,
    cognome_nome VARCHAR(100) NOT NULL,
    a squadra_edizione -nno_nascita  NUMERIC(4) NOT NULL,< 16
);

--convocati
CREATE TABLE Convocati(
    squadra_edizione NUMERIC(4) NOT NULL,
    squadra_nazione VARCHAR(200) NOT NULL,
    numero_maglia INTEGER NOT NULL,
    giocatore NUMERIC(10) NOT NULL REFERENCES Giocatori(id),
    PRIMARY KEY (squadra_edizione, squadra_nazione, numero_maglia)
    FOREIGN KEY (squadra_edizione, squadra_nazione) REFERENCES Squadre(edizione, nazione)
)

----| Esercizi Prova in itinere vecchia | Venerdì 22/10/2021 |----
-- Make sure no giocatore è convocato più volte in una stessa edizione
ALTER TABLE Convocati 
    ADD CONSTRAINT no_doppie_convocazioni UNIQUE (squadra_edizione, giocatore);

-- Vista Palmares che elenca tutte le nazioni che hanno vinto almeno una edizione dei mondiali, 
-- con il numero totale di vittorie
-- Palmares (nazione, numero_vittorie)
CREATE OR REPLACE VIEW Palmares(nazione, numero_vittorie) AS 
    SELECT Edizioni.nazione_vincitrice, count(*)
    FROM Edizioni
    WHERE Edizioni.nazione_vincitrice IS NOT NULL
    GROUP BY Edizioni.nazione_vincitrice

-- Cancellare i giocatori di edizioni passate che avevno meno di 16 anni per la partita
DELETE FROM Convocati AS C
WHERE C.giocatore IN (
    SELECT G.id
    FROM Giocatori AS G
    WHERE C.squadra_edizione - G.anno_nascita < 16
);
-- Oppure
DELETE FROM Convocati AS C
WHERE EXISTS (
    SELECT *
    FROM Giocatori AS G
    WHERE C.squadra_edizione - G.anno_nascita < 16 AND C.giocatore = G.id
);

-- Vista relazionale EtaMedia CHE CALCOLA PER OGNI SQUADRA CHE HA PARTECIPATO 
-- ad una edizione l'età media dei giocatori convocati
CREATE OR REPLACE VIEW EtaMedia(nazione, edizione, eta_media_convocati) AS
    SELECT C.squadra_nazione, C.squadra_edizione, avg(C.squadra_edizione - G.anno_nascita)
    FROM Convocati as C, Giocatori as G
    WHERE C.giocatore = G.id
    GROUP BY C.squadra_nazione, C.squadra_edizione

-- Usare codice parlanti è importante perché ti permette di evitare i join 
-- se le informazioni di cui si ha bisogno si trovano tutte nelle chiavi primarie

-- Estrarre l'elenco dei giocatori che nelle varie edizione sono stati convocati da almeno 2 nazioni distinte
SELECT DISTINCT G.*
FROM Convocati AS C1, Convocati AS C2, Giocatori as G
WHERE C1.squadra_nazione != C2.squadra_nazione AND C1.giocatore = C2.giocatore
    AND C1.giocatore = G.id;

-- Espressione dell'algebra relazionale per il vincolo che impedisce ad un allenatore 
-- di essere omonimo di uno dei convocati della squadra allenata
-- (Non supportate su PostgreSQL | Il DBMS non sa bene come ottimizzarle quindi offre altri strumenti piuttosto lasciando la responsabilità al probgrammatore )
CREATE ASSERTION no_allenatori_giocatori AS
CHECK (
    NOT EXISTS (
        SELECT * 
        FROM Squadre AS S, Convocati AS C, Giocatori AS G
        WHERE S.edizione = C.squadra_edizione AND S.nazione = C.squadra_nazione
            AND C.giocatore = G.id
            AND G.cognome_nome = S.cognome_nome_allenatore
    )
);

-- Per casa
-- espressione_dell_algebra_relazionale = { }

----| END | Venerdì 22/10/2021 |----



------: visite_mediche :------
-- Tabella Medici
CREATE TABLE Medici(
    codice CHAR(16) NOT NULL PRIMARY KEY,
    cognome VARCHAR(16) NOT NULL,
    nome VARCHAR(16) NOT NULL,
    specializzazione VARCHAR(25) NOT NULL,
    telefono NUMERIC(10) NOT NULL
);

-- Tabella Pazienti
CREATE TABLE Pazienti(
    codice_SSN CHAR(16) NOT NULL PRIMARY KEY,
    cognome VARCHAR(16) NOT NULL,
    nome VARCHAR(16) NOT NULL,
    genere CHAR(1) NOT NULL,
    data_nascita DATE NOT NULL,
    residenza VARCHAR(50) NOT NULL
);

-- Tabella Medicinali
CREATE TABLE Medicinali(
    codice NUMERIC(16) NOT NULL PRIMARY KEY,
    nome VARCHAR(16) NOT NULL,
    principio_attivo VARCHAR(32) NOT NULL,
    marca VARCHAR(10) NOT NULL,
    prezzo REAL NOT NULL
);

-- Tabella Visite
CREATE TABLE Visite(
    medico NUMERIC(6) NOT NULL,
    paziente CHAR(16) NOT NULL,
    data DATE NOT NULL,
    diagnosi VARCHAR(60) NOT NULL,
    medicinale NUMERIC(16), -- NULLABLE
    PRIMARY KEY(medico, paziente, data),
    FOREIGN KEY(medicinale) REFERENCES Medicinali(codice)
);

-- Fix mistakes in the first iteration of table creation, because of course there are mistakes in the first iteration
ALTER TABLE Medici 
    ALTER COLUMN codice TYPE CHAR(16);
ALTER TABLE Visite ALTER COLUMN medico TYPE CHAR(16);
ALTER TABLE Visite ADD CONSTRAINT visite_medici_fkey FOREIGN KEY (medico) REFERENCES Medici(codice);
ALTER TABLE Visite ADD CONSTRAINT visite_pazienti_fkey FOREIGN KEY (paziente) REFERENCES Pazienti(codice_ssn);

-- Populate tables with random data
INSERT INTO Medici(codice, cognome, nome, specializzazione, telefono)
VALUES('HUMTGC76U87J987L', 'Crovini', 'Luigi', 'Cardiologia', 5478966657);
INSERT INTO Medici(codice, cognome, nome, specializzazione, telefono)
VALUES('HUMTGC76U87J654L', 'Alberti', 'Dario', 'Ginecoloiga', 9578426544);
INSERT INTO Medici(codice, cognome, nome, specializzazione, telefono)
VALUES('HUMTGC76U87J321L', 'Leonardi', 'Gino', 'Urologia', 5478821456);
INSERT INTO Medici(codice, cognome, nome, specializzazione, telefono)
VALUES('HUMTGC76U87J666L', 'Gervasi', 'Piero', 'Cardiologia', 5471254698);


INSERT INTO Pazienti(codice_ssn, cognome, nome, genere, data_nascita, residenza)
VALUES('JFNHYS76Y76JO98K', 'Alberti', 'Angleo', 'M', '1995-10-13', 'via alfieri 14');
INSERT INTO Pazienti(codice_ssn, cognome, nome, genere, data_nascita, residenza)
VALUES('BGDILM85B84O065J', 'Alessandrini', 'Gilberta', 'F', '1999-05-02', 'via belli 3');

INSERT INTO Medicinali(codice, nome, principio_attivo, marca, prezzo)
VALUES(59746412578945, 'Tachipirina', 'Paracetamolo', 'Bayer', 9.90);
INSERT INTO Medicinali(codice, nome, principio_attivo, marca, prezzo)
VALUES(53766432548946, 'Anticoagulante', 'Rivaroxaban', 'Xaretto', 19.90);

INSERT INTO Visite(medico, paziente, data, diagnosi, medicinale) 
VALUES('HUMTGC76U87J666L', 'JFNHYS76Y76JO98K', '2021-10-13', 'Infarto imminente', 53766432548946);
INSERT INTO Visite(medico, paziente, data, diagnosi, medicinale) 
VALUES('HUMTGC76U87J654L', 'BGDILM85B84O065J', '2021-10-01', 'Nulla', NULL);

SELECT Medici.nome, Pazienti.nome, Medicinali.nome, Visite.data
FROM Medici, Pazienti, Medicinali, Visite
WHERE Visite.medico = Medici.codice
        AND Visite.paziente = Pazienti.codice_ssn
        AND (Visite.medicinale = Medicinali.codice OR Visite.medicinale IS NULL);