package it.unipr.informatica.exam;

public class Worker {
	
	private static int internalCount = 0;
	
	private final int id;
	private final Thread thread;
	
	public Worker() {
		this.id = internalCount++;
		this.thread = new Thread(() -> {
			while (true) {
				Resource[] resources = ResourceManager.get().acquire(id);
				Logger.get().useAndPrint(resources[0], resources[1], resources[2]);
				
				
			}
		})
	}

}
