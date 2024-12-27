-- Se le signature sono diverse le funzioni vengono overloaddate invece che rimpiazzate
CREATE OR REPLACE FUNCTION
    somma(a NUMERIC, b NUMERIC) RETURNS NUMERIC
    AS 
    $BODY$
        BEGIN
            RAISE NOTICE 'sono la somma su numeric'
            RETURN a + b;
        END
    $BODY$
    LANGUAGE plpgsql;


DROP FUNCTION somma (NUMERIC, NUMERIC);

CREATE OR REPLACE FUNCTION 
numero_docenti_per_ateneo(ateneo VARCHAR) RETURNS INTEGER
AS
$BODY$
DECLARE
    risultato INTEGER = 0;
BEGIN
    SELECT count(*) INTO risultato
    FROM organico AS o, atenei AS a
    WHERE o.ateneo = a.codice AND a.descrizione = nome_ateneo;
    RETURN risultato;
END
$BODY$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION
check_codice_fiscale(cf VARCHAR) RETURNS BOOLEAN
AS $BODY$
BEGIN
    RETURN true;
END
$BODY$
LANGUAGE plpgsql;

ALTER TABLE studenti
    ADD CONSTRAINT cf_corretto
    CHECK(check_codice_fiscale(codice_fiscale));

