package net.davoleo.exercises.vectormenu;

import java.util.Scanner;

public class VectorMenuMain {

    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        VectorString vector = new VectorString();

        int choice;

        do {
            System.out.println("Scegli una delle seguenti operazioni: ");
            System.out.println("\t1. Leggi e Memorizza");
            System.out.println("\t2. Ricerca più corta");
            System.out.println("\t3. Ricerca iniziale");
            System.out.println("\t4. Ordina");
            System.out.println("\t5. Stampa");
            System.out.println("\t6. Esci");
            System.out.print("Operazione scelta? ");

            choice = input.nextInt();

            if (vector.isEmpty() && choice > 1)
            {
                System.out.println("Prima devi dare almeno una stringa!");
                continue;
            }

            switch (choice) {
                case 1:
                    System.out.print("Inserire una stringa: ");
                    vector.add(input.next());
                    break;
                case 2:
                    String shortest = vector.getFirstShortest();
                    System.out.println("La stringa più corta è: " + shortest);
                    break;
                case 3:
                    System.out.print("Inserire l'iniziale: ");
                    char capital = input.next().charAt(0);
                    String found = vector.getFirstStartingWith(capital);
                    System.out.println("La prima stringa che inizia per " + capital + " è: " + found);
                    break;
                case 4:
                    vector.sort();
                    System.out.println("Ordinato");
                    break;
                case 5:
                    vector.print();
                    break;
                case 6:
                    System.out.println("Terminato");
                    break;
                default:
                    System.out.println("Scelta non valida! Riprovare");
            }

        } while(choice != 6);

        input.close();
    }
}
