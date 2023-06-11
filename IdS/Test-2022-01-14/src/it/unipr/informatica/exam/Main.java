package it.unipr.informatica.exam;

import java.util.Arrays;

public class Main {
	
	public static final int W = 9;
	
	public static void main(String[] args) {
		Worker[] workers = new Worker[W];
		Arrays.setAll(workers, Worker::new);
		
		for (Worker worker : workers) {
			worker.start();
		}
		
		try {
			Thread.sleep(1000 * 6);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		for (Worker worker : workers) {
			worker.stop();
		}
	}
}
