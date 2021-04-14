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

        System.out.println("Inserisci 3 numeri: ");

        //Crea un oggetto di tipo Scanner e lo assegna alla reference scanner
        Scanner scanner = new Scanner(System.in);

        //Analizza ed estrae un intero (se riesce) dalla stringa in System.in
        x = scanner.nextInt(); 
        y = scanner.nextInt();
        z = scanner.nextInt();

        //Typecasting della costante 3 a float
        float average = (x + y + z) / 3F;

        //Concatenazione tra stringhe
        System.out.println("La media è: " + average);

        scanner.close();
    }
}