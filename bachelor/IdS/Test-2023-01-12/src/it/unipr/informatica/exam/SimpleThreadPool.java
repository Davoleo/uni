package it.unipr.informatica.exam;

public class SimpleThreadPool {
	private final Worker[] workers;
	private final BlockingLinkedQueue<Runnable> tasks;
	
	public SimpleThreadPool(int size) {
		this.tasks = new BlockingLinkedQueue<Runnable>();
		this.workers = new Worker[size];
		
		for (int i = 0; i < size; i++) {
			workers[i] = new Worker();
			workers[i].start();
		}
	}
	
	public void execute(Runnable task) {
		tasks.enqueue(task);
	}
	
	public void shutdown() {
		for (Worker worker : workers) {
			worker.shutdown();
		}
	}

	private class Worker extends Thread {
		
		private boolean shutdown = false;
		
		@Override
		public void run() {
			while (true) {	
				synchronized (this) {
					if (shutdown) {
						//System.out.println(this.getName() + " Exiting Gracefully.");
						return;
					}
				}
				
				try {
					Runnable task = tasks.take();
					task.run();
				} catch (InterruptedException e) {
					//System.out.println(this.getName() + " Interrupted!");
					return;
				}
			}	
		}
		
		public synchronized void shutdown() {
			shutdown = true;
			this.interrupt();
		}
	}
	
}
