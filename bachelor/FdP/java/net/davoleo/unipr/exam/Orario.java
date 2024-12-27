package net.davoleo.unipr.exam;

/**
 * Studente: ***REDACTED***
 * Numero compito: 21
 */
public class Orario {
    private int h;
    private int m;
    private int s;

    /**
     * Controlla se i parametri del metodo sono corretti e nel caso lo siano assegna i valori alle variabili interne
     * altrimenti lancia un eccezione con il messaggio corretto
     */
    private void controllaOrario(int hours, int minutes, int seconds) {
        if (hours > 23 || hours < 0) {
            throw new OrarioFormatException("Il formato dell'ora non è corretto");
        }
        else if (minutes > 59 || minutes < 0) {
            throw new OrarioFormatException("Il formato dei minuti non è corretto");
        }
        else if (seconds > 59 || seconds < 0) {
            throw new OrarioFormatException("Il formato dei secondi non è corretto");
        }
        else {
            this.h = hours;
            this.m = minutes;
            this.s = seconds;
        }
    }

    // ---- Constructors ----
    /**
     * Crea un nuovo oggetto di tipo Orario partendo dagli interi corrispondenti rispettivamente a ore minuti e secondi
     * @param h le ore
     * @param m i minuti
     * @param s i secondi
     * @throws OrarioFormatException Lanciata nel caso il formato di 1 dei 3 parametri che rappresentano i dati non sia nel range di correttezza
     */
    public Orario(int h, int m, int s) throws OrarioFormatException
    {
        //Controlla e assegna campi interni
        controllaOrario(h, m, s);
    }

    /**
     * Crea un nuovo oggetto di tipo Orario a partire da un numero di secondi
     * @param seconds I secondi corrispondenti ad un certo orario
     */
    public Orario(int seconds)
    {
        int hours = seconds / 3600;
        seconds %= 3600;
        int minutes = seconds / 60;
        seconds %= 60;

        //Controlla e assegna campi interni
        controllaOrario(hours, minutes, seconds);
    }

    /**
     * Crea un nuovo oggetto Orario copiando i valori interni da un'altro oggetto
     * I due oggetti prodotti sono indipendenti tra di loro e non condividono nessun puntatore di memoria
     * @param other L'oggetto da copiare
     * @throws OrarioFormatException Lanciata nel caso per qualche motivo i dati interni dell'altro orario siano compromessi
     */
    public Orario(Orario other) throws OrarioFormatException
    {
        //Controlla e assegna campi interni
        controllaOrario(other.h, other.m, other.s);
    }

    // ---- Utility Methods ----

    /**
     * @param object Oggetto con cui this è confrontato
     * @return vero se l'oggetto orario stesso può essere considerato uguale a quello passato nel parametro
     */
    @Override
    public boolean equals(Object object) {
        //Se l'oggetto non appartiene alla classe orario è impossibile che sia uguale all'oggetto
        if (object instanceof Orario) {
            Orario other = ((Orario) object);
            //Se invece appartiene può essere uguale se e solo se tutti i campi interni della classe sono uguali
            return this.h == other.h && this.m == other.m && this.s == other.s;
        }
        else
            return false;
    }

    /**
     * @return La rappresentazione in forma di stringa dell'orario nel formato H:M:S
     */
    @Override
    public String toString()
    {
        return h + ":" + m + ':' + s;
    }

    /**
     * @return vero se questo orario è minore dell'orario passato come parametro
     */
    public boolean lessThan(Orario orario) {
        if (this.h < orario.h)
            return true;
        else if (this.h > orario.h)
            return false;
        else {
            if (this.m == orario.m)
                return this.s < orario.s;
            else
                return this.m < orario.m;
        }
    }

    /**
     * @param other Orario da aggiungere a this
     * @return una nuova istanza di un oggetto di tipo Orario a cui è stato aggiunto il valore di un altro orario
     * @throws OrarioFormatException se l'orario risultante va in overflow rispetto alle 24 ore della giornata.
     */
    public Orario add(Orario other) throws OrarioFormatException {
        boolean riporto = false;

        int newSeconds = this.s + other.s;
        if (newSeconds > 59) {
            riporto = true;
            newSeconds -= 60;
        }

        int newMinutes = this.m + other.m + (riporto ? 1 : 0);
        riporto = false;
        if (newMinutes > 59) {
            riporto = true;
            newMinutes -= 60;
        }
        int newHours = this.h + other.h + (riporto ? 1 : 0);

        return new Orario(newHours, newMinutes, newSeconds);
    }

    /**
     * Aggiunge un orario corrispondente ad un certo amount di secondi a this orario
     * @param seconds quantità di secondi da aggiugnere all'orario
     * @return un nuovo orario indipendente dal primo a cui è stato sommato la quantità in secondi
     * @throws OrarioFormatException se l'orario risultante va in overflow rispetto alle 24 ore della giornata.
     */
    public Orario add(int seconds) throws OrarioFormatException {
        Orario fromSeconds = new Orario(seconds);
        return this.add(fromSeconds);
    }

    /**
     * @return la quantità in secondi rappresentante l'orario del giorno
     */
    public int toSeconds() {
        return this.h * 3600 + this.m * 60 + this.s;
    }

    // -------- GETTERS ----------//

    /**
     * @return le ore dell'orario
     */
    public int getHours()
    {
        return h;
    }

    /**
     * @return i minuti dell'orario
     */
    public int getMinutes()
    {
        return m;
    }

    /**
     * @return i secondi dell'orario
     */
    public int getSeconds()
    {
        return s;
    }
}
