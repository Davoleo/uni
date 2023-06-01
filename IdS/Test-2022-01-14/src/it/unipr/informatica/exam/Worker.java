package it.unipr.informatica.exam;

public class Worker {
	
	private static int internalCount = 0;
	
	private final int id;
	private final Thread thread;
	
	public Worker() {
		this.id = internalCount++;
		this.thread = new Thread(() -> {
			while (true) {
				Resource[] resources;
				
				try {
					resources = ResourceManager.get().acquire(id);
					
					Logger.get().useAndPrint(resources[0], resources[1], resources[2]);
					
					for (Resource resource : resources)
						resource.release();
					System.out.println("Worker" + id + ": released resources [" + resources[0].getID() + "-" + resources[1].getID() + "-" + resources[2].getID() + ']');
					
					Thread.sleep(100);
				} 
				catch (InterruptedException e) {
					System.out.println("Worker" + id + ": Interrupted while acquiring resources!");
					return;
				}
				catch (IllegalStateException e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	public void start() {
		this.thread.start();
	}
	
	public void stop() {
		this.thread.interrupt();
	}

}
