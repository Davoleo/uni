package net.davoleo.unipr.exam;

/**
 * Studente: Leonardo Davoli
 * Numero compito: 21
 *
 * Lanciata quando si incontra un errore di formato nel range di valori della classe {@link Orario}
 */
public class OrarioFormatException extends RuntimeException {

    public OrarioFormatException(String message)
    {
        super(message);
    }
}
