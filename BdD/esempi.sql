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


SELECT nome, reddito
FROM Persone
WHERE eta < 30;