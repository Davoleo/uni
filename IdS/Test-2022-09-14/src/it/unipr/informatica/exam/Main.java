package it.unipr.informatica.exam;

import java.util.Arrays;

public class Main {
	
	public static final int N = 50;
	public static final int M = 20;
	
	public static void main(String[] args) {
		ResourceManager manager = new ResourceManagerImpl(N);
		
		Worker[] workers = new Worker[M];
		Arrays.setAll(workers, (i) -> new Worker(manager));
		
		for (Worker worker : workers) {
			worker.start();
		}
		
		try {
			Thread.sleep(6 * 1000);
		} catch (InterruptedException e) {
			System.out.println("Interrupted Main thread while sleeping");
		}
		
		for (Worker worker : workers) {
			worker.interrupt();
		}	
	}
}
