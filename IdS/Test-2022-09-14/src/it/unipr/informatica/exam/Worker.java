package it.unipr.informatica.exam;

import java.util.Random;

public class Worker extends Thread {
	
	private static final Random RANDOM = new Random();
	private final ResourceManager resourceManager;
	
	public Worker(ResourceManager manager) {
		this.resourceManager = manager;
	}
	
	@Override
	public void run() {
		while (true) {
			int i = RANDOM.nextInt(Main.N);
			int j = RANDOM.nextInt(Main.N);
		
			try {	
				resourceManager.acquireResources(i, j);
				System.out.println(getName() + " Acquired Resources: " + i + '&' + j);
				
				Thread.sleep(100 + i + j);
				
				resourceManager.freeResources(i, j);
				System.out.println(getName() + " Released Resources: " + i + '&' + j);
				
			} catch (InterruptedException e) {
				System.err.println(getName() + " Interrupted while working!");
				return;
			}
			catch (RuntimeException e) {
				System.err.println(e.getMessage());
				return;
			}
		}
	}

}
