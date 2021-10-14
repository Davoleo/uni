--nazioni(nome)
CREATE TABLE NAZIONI(
    NOME VARCHAR(100) NOT NULL,
    PRIMARY KEY (NOME)
);

--edizioni(anno, nazione ospitante, nazione vincitrice)
CREATE TABLE EDIZIONI (
    ANNO NUMERIC(4) NOT NULL,
    NAZIONE_OSPITANTE VARCHAR(100) NOT NULL,
    NAZIONE_VINCITRICE VARCHAR(100), -- nullable
    PRIMARY KEY (ANNO),
    FOREIGN KEY (NAZIONE_OSPITANTE) REFERENCES NAZIONI(NOME)
    FOREIGN KEY (NAZIONE_VINCITRICE) REFERENCES NAZIONI(NOME)
)

--squadre()
CREATE TABLE SQUADRE (
    EDIZIONE NUMERIC(4) NOT NULL,
    NAZIONE VARCHAR(100) NOT NULL,
    COGNOME_NOME_ALLENATORE VARCHAR(100)
)
--modifica dello schema della tabella
ALTER TABLE SQUADRE
    ADD CONSTRAINT SQUADRE_KEY PRIMARY KEY (EDIZIONE, NAZIONE);
ALTER TABLE SQUADRE
    ADD CONSTRAINT SQUADRE_EDIZIONE_FKEY 
    FOREIGN KEY (EDIZIONE) REFERENCES EDIZIONI(ANNO);
ALTER TABLE SQUADRE
    ADD CONSTRAINT SQUADRE_NAZIONE_FKEY 
    FOREIGN KEY (NAZIONE) REFERENCES NAZIONI(NOME);
ALTER TABLE SQUADRE 
    ALTER COLUMN COGNOME_NOME_ALLENATORE SET NOT NULL;

-- NUOVA SIGLA CIFC: CODE IS FUCKING CODE (@Zambo-dev)

--giocatori(id, cognome nome, anno nascita)
CREATE TABLE GIOCATORI(
    ID NUMERIC(10) NOT NULL PRIMARY KEY,
    COGNOME_NOME VARCHAR(100) NOT NULL,
    ANNO_NASCITA NUMERIC(4) NOT NULL,
)

--convocati
CREATE TABLE CONVOCATI(
    SQUADRA_EDIZIONE NUMERIC(4) NOT NULL,
    SQUADRA_NAZIONE VARCHAR(200) NOT NULL,
    NUMERO_MAGLIA INTEGER NOT NULL,
    GIOCATORE NUMERIC(10) NOT NULL REFERENCES GIOCATORI(ID),
    PRIMARY KEY (SQUADRA_EDIZIONE, SQUADRA_NAZIONE, NUMERO_MAGLIA)
    FOREIGN KEY (SQUADRA_EDIZIONE, SQUADRA_NAZIONE) REFERENCES SQUADRE(EDIZIONE, NAZIONE)
)

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