package it.unipr.informatica.exam;

import java.util.ArrayList;
import java.util.List;

public class Main {
	
	public final static int R = 9;
	public final static int L = 9;

	public static void main(String[] args) {		
		
		// laborer
		List<Laborer> laborers = new ArrayList<>(L);
		for (int i=0; i<L; ++i) {
			laborers.add(new Laborer(i));
			laborers.get(i).start();
		}
		
		// timer -> 5 s
		try {
			Thread.sleep(1000 * 5);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		
		// shutdown
		for (int i=0; i<L; ++i) {
			laborers.get(i).interrupt();
		}
		
		
		System.out.println("Terminated");
	}
}
