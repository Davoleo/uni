import java.util.Scanner;

public class HelloWorld {
    //campo dati
    private int x;

    //Costruttore
    public HelloWorld() {

    }

    //Metodo
    public void print() {

    }

    //Metodo Main (chiamato all'inizio dell'avvio del programma)
    public static void main(String[] args) {
        private int x, y, z;

        System.out.print("Quanti numeri vuoi dare? (> 0): ");

        //Crea un oggetto di tipo Scanner e lo assegna alla reference scanner
        Scanner scanner = new Scanner(System.in);

        int count;
        do {
            count = scanner.nextInt();
            if (n > 0)
                break;
            else
                System.out.println("Valore non valido. Ripetere")
        }
        while (true);

        int sum = 0;
        int num;
        for (int i = 0; i < count; i++) {
            System.out.print("Inserisci un numero: ");
            num = scanner.nextInt();
            sum += num;
        }

        float average = (float) sum / num;

        System.out.println("La media è: " + average + " | La somma è " + sum);
        scanner.close();
    }
}