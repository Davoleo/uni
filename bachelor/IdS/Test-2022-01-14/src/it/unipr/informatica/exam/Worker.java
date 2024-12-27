package it.unipr.informatica.exam;

public class Worker  {
	
	private final int id;
	private final Thread thread;
	
	public Worker(int id) {
		this.id = id;
		this.thread = new Thread(this::loop);
	}
	
	private void loop() {
		ResourceManager manager = ResourceManager.get();
		while (true) {
			try {

				//Una synchronized sull'array qui aggiusta i problemi di race condition ma allo stesso tempo rovina tutto il parallelismo del sistema rendendolo seriale...
				//synchronized (manager.getAllResources()) {
				Resource[] resources = manager.acquire(id);

				Logger.get().useAndPrint(resources[0], resources[1], resources[2]);

				for (Resource resource : resources) {
					resource.release();
					manager.notifyRelease(resource.getID());
				}
				//}
				
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
	}
	
	public void start() {
		this.thread.start();
	}
	
	public void stop() {
		this.thread.interrupt();
	}

}
