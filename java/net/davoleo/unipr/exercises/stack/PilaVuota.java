package net.davoleo.unipr.exercises.stack;

public class PilaVuota extends RuntimeException {

    public PilaVuota()
    {
        super("Lo stack è vuoto!");
    }

}
