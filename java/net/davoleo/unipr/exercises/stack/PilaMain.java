package net.davoleo.unipr.exercises.stack;

public class PilaMain {
  
	   public static void main (String[] args) {
	        try {		    	    
	     
	          Pila b = new PilaVector();		    
	          System.out.println("La pila 'b' e' " + b);
	          
	          b.push("aaa");
              b.push("bbb");
              b.push("ccc");
	          System.out.println("La pila 'b' e' " + b);
	          
              System.out.println("Elemento estratto dalla pila 'b': " + b.pop());
	          if (!b.isEmpty()) System.out.println("La pila 'b' e' " + b);
	          
	          System.out.println("La pila 'b' ha " + b.size() + " elementi");
	          
	          Pila copiaDi_b = (PilaVector)((PilaVector)b).clone();
	          System.out.println("La pila 'copiaDi_b' e' " + copiaDi_b);
	          copiaDi_b.pop();
	          System.out.println("La pila 'copiaDi_b' modificata e' " + copiaDi_b);	
	          System.out.println("La pila 'b' e' rimasta invariata: " + b);	
	          
	          b.clear();
	          System.out.println("Ora la pila 'b' e' " + b + "\n");

	          Pila c = new PilaList();		    
	          System.out.println("La pila 'c' e' " + c);
	          
	          c.push(3.1);
	          c.push(5.4);
              c.push(2.3);
	          System.out.println("La pila 'c' e' " + c);
	          
	          System.out.println("Elemento estratto dalla pila 'c': " + c.pop());
	          if (!c.isEmpty()) System.out.println("La pila 'c' e' " + c);	
	          
	          System.out.println("La pila 'c' ha " + c.size() + " elementi");
	          
	          Pila copiaDi_c = (PilaList)((PilaList)c).clone();
	          System.out.println("La pila 'copiaDi_c' e' " + copiaDi_c);
	          copiaDi_c.pop();
	          System.out.println("La pila 'copiaDi_c' modificata e' " + copiaDi_c);	
	          System.out.println("La pila 'c' e' rimasta invariata: " + c);	
	          
	          c.clear();
	          System.out.println("Ora la pila 'c' e' " + c + "\n");
	          
			  //test metodo specifico di PilaVector
	          Pila a = new PilaVector();
	          a.push(1);
	          a.push(4);
	          System.out.println("La pila 'a' e' " + a);
	          
	          int x = (Integer)((PilaVector)a).get(1);  
	          System.out.println("Elemento estratto da 'a': " + x + '\n');	
	          
	          a.clear();
	          a.pop();
	          
	        }
	        catch (PilaVuota e) {
	        	System.out.println("Errore: pop su pila vuota\n");
	        }
	        catch (Throwable e) {    // catch all
	        	System.out.print("Altre eccezioni: ");
	        	System.out.println(e);
	        }
	        		    
	    }   
	}


/* Traccia esecuzione 
	  
La pila 'b' e' []
La pila 'b' e' [aaa,bbb,ccc]
Elemento estratto dalla pila 'b': ccc
La pila 'b' e' [aaa,bbb]
La pila 'b' ha 2 elementi
La pila 'copiaDi_b' e' [aaa,bbb]
La pila 'copiaDi_b' modificata e' [aaa]
La pila 'b' e' rimasta invariata: [aaa,bbb]
Ora la pila 'b' e' []

La pila 'c' e' []
La pila 'c' e' [2.3,5.4,3.1]
Elemento estratto dalla pila 'c': 2.3
La pila 'c' e' [5.4,3.1]
La pila 'c' ha 2 elementi
La pila 'copiaDi_c' e' [5.4,3.1]
La pila 'copiaDi_c' modificata e' [3.1]
La pila 'c' e' rimasta invariata: [5.4,3.1]
Ora la pila 'c' e' []

La pila 'a' e' [1,4]
Elemento estratto da 'a': 4

Errore: pop su pila vuota

*/

