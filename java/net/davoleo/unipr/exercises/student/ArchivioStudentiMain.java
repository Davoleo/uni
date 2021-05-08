package net.davoleo.unipr.exercises.student;

public class ArchivioStudentiMain {
  
       public static void main (String[] args) {
               ArchivioStudenti A = new ArchivioStudenti(); 
               
               Studente s1 = new Studente("aaa","mmm",111);
               s1.stampa(System.out);
                  
               A.aggiungi(s1);
               A.aggiungi(new Studente("bbb","nnn",222));
               A.aggiungi(new Studente("ccc","ooo",333));
               
               System.out.println("\nL'archivio e': ");
               A.stampa(System.out);

               Studente s2 = A.ricerca(222);
               if (s2 != null) {
                   System.out.println("Studente trovato: ");
                   s2.stampa(System.out);
               }    
               else 
                   System.out.println("Studente non trovato");
               
               System.out.println();
               Studente s3 = A.ricerca(444);
               if (s3 != null) {
                   System.out.println("Studente trovato: ");
                   s3.stampa(System.out);
               }    
               else 
                   System.out.println("Studente non trovato");
               
               System.out.println();
               if (A.aggiungi(new Studente("ddd","ppp",111)))
                   System.out.println("Aggiunto un altro studente");
               else 
                   System.out.println("Studente non aggiunto perch� gi� presente");     
        }                 
    }


/* Traccia esecuzione 
      
Aaa Mmm
matricola: 111
email: aaa.mmm@studenti.unipr.it

L'archivio e': 
Aaa Mmm
matricola: 111
email: aaa.mmm@studenti.unipr.it

Bbb Nnn
matricola: 222
email: bbb.nnn@studenti.unipr.it

Ccc Ooo
matricola: 333
email: ccc.ooo@studenti.unipr.it

Studente trovato: 
Bbb Nnn
matricola: 222
email: bbb.nnn@studenti.unipr.it

Studente non trovato

Studente non aggiunto perch� gi� presente

*/

