-- Esempio 0a
SELECT i.*
FROM impiegati as i
WHERE i.stipendio > 40;

-- Esempio 0a
SELECT i.matricola, i.nome, i.eta 
FROM impiegati as i;

-- Esempio 2
SELECT s.capo 
FROM impiegati AS i, supervisione AS s 
WHERE i.stipendio > 40 AND i.matricola = s.impiegato;

-- Esempio 3
SELECT c.nome, c.stipendio
FROM impiegati AS i, supervisione AS s, impiegati AS c
WHERE i.stipendio > 40 AND i.matricola = s.impiegato AND c.matricola = s.capo;

-- Esempio 4
SELECT c.matricola AS MATC, c.nome AS NOMEC, c.stipendio AS STIPENDIOC, i.matricola, i.nome, i.stipendio
FROM impiegati AS i, supervisione AS s, impiegati AS c
WHERE i.stipendio > c.stipendio AND i.matricola = s.impiegato AND c.matricola = s.capo;

-- Esempio 5
SELECT c.matricola AS MATC, c.nome AS NOMEC
FROM supervisione AS s, impiegati AS c
WHERE c.matricola = s.capo AND NOT EXISTS(
    SELECT *
    FROM impiegati AS i, supervisione AS s1
    WHERE i.matricola = s1.impiegato AND s1.capo = c.matricola AND i.stipendio <= 40
);