package net.davoleo.unipr.exercises.student;

import java.io.PrintStream;

public class Studente extends Persona {

    private int matricola;
    private String email;

    public Studente()
    {
        matricola = 0;
        email = "xxx";
    }

    public Studente(String name, String surname, int matricola)
    {
        super(name, surname);
        this.matricola = matricola;
        email = name + '.' + surname + "@studenti.unipr.it";
    }

    public int getMatricola()
    {
        return matricola;
    }

    @Override
    void stampa(PrintStream stream)
    {
        super.stampa(stream);
        stream.println("matricola: " + matricola);
        stream.println("email: " + email);
    }
}
