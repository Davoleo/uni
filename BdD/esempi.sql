CREATE TABLE Impiegato(
    matricola CHAR(6) NOT NULL PRIMARY KEY,
    nome CHAR(20) NOT NULL,
    cognome CHAR(20) NOT NULL,
    dipart CHAR(15), --nullable
    stipendio NUMERIC(9) DEFAULT 0, --valore di default se non inserito quando si aggiungono ennuple
    FOREIGN KEY (dipart) REFERENCES Dipartimento(nomedip),
    UNIQUE (cognome, nome) -- chiave ma non primaria
);

-- Non funziona su DB2 e SQLServer (2009)
CREATE DOMAIN Voto 
    AS SMALLINT DEFAULT NULL
    CHECK (value >= 18 AND value <= 30);

-- Join esplicito
SELECT madre, paternita.figlio, padre, madre FROM maternita JOIN paternita ON paternita.figlio = maternita.figlio

SELECT madre, figlio, padre FROM maternita NATURAL JOIN paternita;

-- Ordine
SELECT nome, reddito 
FROM persone
WHERE eta < 30
ORDER BY nome;

SELECT nome, reddito
FROM Persone
WHERE eta < 30;


SELECT padre, count(*) AS numFigli
FROM Paternita
GROUP BY padre


-- clausola HAVING: selezione su operatori di aggregazione
SELECT padre, AVG(Fi.reddito)
FROM Persone as Fi JOIN Paternita ON figlio = nome
GROUP BY padre
HAVING AVG(Fi.reddito) > 25


SELECT d.descrizione, count(*) as numero_docenti
FROM atenei AS a, dipartimenti AS d, organico AS o
WHERE a.codice = d.ateneo AND a.descrizione = 'PARMA' AND d.ateneo = o.ateneo AND d.codice = o.dipartimento
GROUP BY d.ateneo, d.codice, d.descrizione
ORDER BY d.descrizione

-- clausola insert
-- Attributi impliciti | Se non ci sono 3 attributi -> Errore
-- Non si capisce bene di quali attributi si tratta
INSERT INTO Persone VALUES('Mario', 25, 52);

INSERT INTO Persone(nome, eta, reddito) VALUES('Pino', 25, 52);
-- Di principio non è errore | 
-- gli attributi rimanenti ricevono il valore di DEFAULT, altrimenti NULL nel caso il DEFAULT non sia specificato.
INSERT INTO Persone(nome, reddito) VALUES('Lino', 55);

-- Aggiungiamo tutte le persone nella relazione padre che non si trovavano ancora nella relazione persone
INSERT INTO Persone (nome) 
SELECT padre
FROM Paternita
WHERE padre NOT IN (SELECT nome FROM persone);

-- Se NULL rimane
-- DELETE FROM usa una sola tabella (NO JOIN, non sono standard)
DELETE FROM Persone WHERE eta < 35;
DELETE FROM Paternita WHERE figlio NOT IN (SELECT nome FROM persone);

-- Cancella tutte le ennuple da Paternita
DELETE FROM Paternita

UPDATE Persone SET reddito = 45 WHERE nome = 'Piero';

UPDATE Persone SET reddito = reddito * 1.1 WHERE eta < 30;