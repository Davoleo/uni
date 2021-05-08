package net.davoleo.unipr.exercises.student;

import java.io.PrintStream;

public class ArchivioStudenti {

    public Studente[] array;
    public int size;

    public ArchivioStudenti()
    {
        array = new Studente[100];
        size = 0;
    }

    public boolean aggiungi(Studente studente)
    {
        if (size >= 100)
            return false;

        for (int i = 0; i < size; i++)
        {
            if (array[i].getMatricola() == studente.getMatricola())
                return false;
        }

        array[size++] = studente;
        return true;
    }

    public Studente ricerca(int matricola)
    {
        for (int i = 0; i < size; i++)
        {
            if (array[i].getMatricola() == matricola)
                return array[i];
        }

        return null;
    }

    public void stampa(PrintStream stream)
    {
        stream.println("Log dell'archivio:");
        for (int i = 0; i < size; i++)
        {
            array[i].stampa(stream);
            stream.println();
        }
    }
}
