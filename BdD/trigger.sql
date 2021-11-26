-- in funzioni e procedure non si possono chiamare statement che interferiscono con la transazione:
-- NO COMMIT, NO BEGIN TRANSACTION, NO ROLLBACK

-- non ritorna un vero TRIGGER ma bisogna metterlo 
-- per fare in modo che venga considerata una funziona chiamabile da un trigger
CREATE OR REPLACE FUNCTION alessandro_immortale() RETURNS TRIGGER AS 
$BODY$
BEGIN
    -- DELETE: new contiene NULL mentre old contiene la vecchia riga
    -- UPDATE: new contiene il nuovo valore old contiene il vecchio valore
    -- INSERT: new è la riga appena inserita old contiene NULL
    IF (OLD.nome = 'Alessandro' AND (NEW.nome IS NULL OR NEW.nome != OLD.nome))
    THEN 
    RAISE EXCEPTION 'non toccare alessandro! gsoidfjklgj'
    END IF;
    -- le funzioni che lavorano su trigger devono restituire il numero della riga su cui stanno lavorando
    RETURN NEW;
END
$BODY$
LANGUAGE plpgsql;

-- Esempio di Trigger per implementare un vincolo di ennupla
CREATE TRIGGER alessandro_immortale_trig
BEFORE DELETE OR UPDATE ON organico
FOR EACH ROW 
EXECUTE PROCEDURE alessandro_immortale();


-----------------------------------------------


--Cambia i nomi e cognomi dell'anagrafica in modo che siano normalizzati
CREATE FUNCTION anagrafica_normalizzare() RETURNS TRIGGER AS
$BODY$
BEGIN
    new.cognome := upper(new.cognome);
    new.nome := initcap(new.nome);
    RETURN new;
END
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER anagrafica_normalizzata_trig
BEFORE INSERT ON anagrafica
FOR EACH ROW
EXECUTE PROCEDURE anagrafica_normalizzata();

