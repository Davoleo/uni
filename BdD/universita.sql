-- CorsiLaurea(codice_pk, nome, descrizione)
CREATE TABLE CorsiLaurea(
    codice INTEGER NOT NULL PRIMARY KEY,
    nome VARCHAR(64) NOT NULL,
    descrizione VARCHAR(250) NOT NULL,
    numero_anni_corso INTEGER NOT NULL
);
----------
-- Insegnamenti(codice_pk, nome, crediti, ssd)
CREATE TABLE Insegnamenti(
    codice INTEGER NOT NULL PRIMARY KEY,
    nome VARCHAR(64) NOT NULL,
    crediti INTEGER NOT NULL,
    ssd VARCHAR(16) NOT NULL
);

-- Manifesti(laurea_pk_fk, insegnamento_pk_fk, fondamentale(boolean), anno_corso)
CREATE TABLE Manifesti(
    laurea INTEGER NOT NULL REFERENCES CorsiLaurea(codice),
    insegnamento INTEGER NOT NULL REFERENCES Insegnamenti(codice),
    fondamentale BOOLEAN NOT NULL,
    anno_corso INTEGER NOT NULL,
    PRIMARY KEY (laurea, insegnamento)
);

-- Studenti(matricola_pk, nome, cognome, data_nascita)
CREATE TABLE Studenti(
    matricola INTEGER NOT NULL PRIMARY KEY,
    nome VARCHAR(32) NOT NULL,
    cognome VARCHAR(32) NOT NULL,
    data_nascita DATE NOT NULL
);

-- Iscrizioni(studente_pk_fk, anno_iscrizione_pk, laurea_fk, data_iscrizione, anno_corso)
CREATE TABLE Iscrizioni(
    studente INTEGER NOT NULL REFERENCES Studenti(matricola),
    anno_iscrizione INTEGER NOT NULL,
    laurea INTEGER NOT NULL REFERENCES CorsiLaurea(codice),
    data_iscrizione DATE NOT NULL,
    anno_corso INTEGER NOT NULL, -- Primo, secondo anno e così via
    PRIMARY KEY(studente, anno_iscrizione)
);

ALTER TABLE
ADD CONSTRAINT anno_corso_valido
CHECK (anno_corso >= 1 AND anno_corso <= 6);

-- 1. estrarre i nomi dei corsi si laurea il cui manifesto comprende un insegnamento di informatica 
-- (ssd uguale a INF/01 oppure ING-ING/05) come corso fondamentale;
SELECT DISTINCT cors.nome
FROM Insegnamenti AS ins, Manifesti AS man, CorsiLaurea AS cors
WHERE ins.codice = man.insegnamento AND cors.codice = man.laurea 
    AND (ins.ssd = 'INF/01' OR ins.ssd = 'ING-INF/05') AND man.fondamentale

-- 2. Per ogni corso di laurea, estrarre le date di nascita 
-- dello studente più giovane e dello studente più vecchio iscritti a tale corso nell'anno 2012
SELECT cors.nome AS corso_laurea, max(stud.data_nascita) AS nascita_giovane, min(stud.data_nascita) AS nascita_vecchio
FROM Iscrizioni AS iscr, CorsiLaurea AS cors, Studenti AS stud
WHERE iscr.studente = stud.matricola AND iscr.laurea = cors.codice
    AND iscr.anno_iscrizione = 2012
GROUP BY cors.nome;

-- 3. estrarre l'elenco degli insegnamenti che compaiono come fondamentali in almeno 3 corsi di laurea
SELECT ins.codice AS codice, ins.nome AS insegnamento
FROM Insegnamenti AS ins, Manifesti AS man
WHERE ins.codice = man.insegnamento AND man.fondamentale
GROUP BY ins.codice, ins.nome
HAVING count(*) >= 3;

-- 4. per ogni insegnamento calcolare il numero (presunto) di studenti iscritti nell'anno 2012 che frequentano l'insegnamento; 
-- uno studente è frequentante se l'insegnamento compare nel piano degli studi del corso al quale è iscritto ed 
-- è erogato nello stesso anno di corso dello studente
SELECT ins.codice, ins.nome, count(*) AS numero_ipotetico_frequentanti
FROM Insegnamenti AS ins, Iscrizioni AS iscr, Manifesti AS man
WHERE ins.codice = man.insegnamento AND iscr.laurea = man.laurea
    AND iscr.anno_iscrizione = 2012 AND iscr.anno_corso = man.anno_corso
GROUP BY ins.codice, ins.nome;

-- per ogni studente che nel 2020 era iscritto all'anno N del corso di laurea CL e N < del numero di anni del corso del CL
-- iscrivilo per l'anno 2021 all'anno di corso N+1 in data odierna
INSERT INTO Iscrizioni(studente, anno_iscrizione, laurea, data_iscrizione, anno_corso)
SELECT iscr.studente, 2021, iscr.laurea, CAST('today' AS DATE), iscr.anno_corso + 1
    FROM Iscrizioni AS iscr, CorsiLaurea AS cors
    WHERE iscr.laurea = cors.codice
        AND iscr.anno_iscrizione = 2020 AND iscr.anno_corso < cors.numero_anni_corso

-- modificare gli insegnamenti dei settori di informatica portando a 6 CFU quelli da 5 CFU e a 9 CFU quelli da 10 CFU
-- [no condizionali nel parziale]
UPDATE Insegnamenti 
SET crediti = 
    CASE crediti
        WHEN 5 THEN 6
        WHEN 10 THEN 9
        ELSE crediti
    END
WHERE ssd IN ('INF/01', 'ING-INF/05') AND crediti = 5;

-- 5. esprimere come espressione dell'algebra relazionale 
-- il vincolo che impone che ogni studente sia maggiorenne quando effettua l'iscrizione ad un corso
-- [Espressione che estrae le ennuple che violano il vincolo = { }]
-- in relational_algebra.tex