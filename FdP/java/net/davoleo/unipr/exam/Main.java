package net.davoleo.unipr.exam;

import java.util.Scanner;

/**
 * Studente: ***REDACTED***
 * Numero compito: 21
 */
public class Main {

    public static void main(String[] args)
    {
        //Inizializzo un nuovo scanner per Standard Input
        Scanner scanner = new Scanner(System.in);

        //Input dell'orario
        System.out.println("Inserisci 3 numeri nel formato (h m s): ");
        int hours = scanner.nextInt();
        int minutes = scanner.nextInt();
        int seconds = scanner.nextInt();

        try {
            //Creazione dell'istanza dell'orario
            Orario s1 = new Orario(hours, minutes, seconds);
            System.out.println(s1);

            //Creazione di un orario con cui comparare l'orario di input
            Orario test = new Orario(12, 0, 0);
            if (s1.lessThan(test))
                System.out.println("L'orario s1 precede le 12:00:00");
            else if (s1.equals(test))
                System.out.println("L'orario s1 è uguale alle 12:00:00");
            else
                System.out.println("L'orario s1 è successivo alle 12:00:00");

            //Test del metodo di somma tra orari
            System.out.println(s1.add(1000));

            //test del costruttore di copia
            Orario s1bis = new Orario(s1);
            System.out.println(s1bis);
        }
        catch (OrarioFormatException e) {
            System.out.println("Errore! " + e.getMessage());
        }
    }

}
