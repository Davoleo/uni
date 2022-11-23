package net.davoleo.uni.concurrent;

//Package scope -> to avoid end user creating instances of this class directly 
class SimpleThreadPoolExecutorService implements ExecutorService {

	private Worker[] workers;
	private BlockingQueue<Runnable> tasks;
	private boolean shutdown;
	
	SimpleThreadPoolExecutorService(int count) {
		if (count < 1)
			throw new IllegalArgumentException("count < 1");
		
		this.shutdown = false;
		this.tasks = new LinkedBlockingQueue<>();
		
		this.workers = new Worker[count];
		
		for (int i = 0; i < count; ++i) {
			Worker worker = new Worker();
			workers[i] = worker;
			worker.start();
		}
	}
	
	@Override
	public void execute(Runnable command) {
		if (command == null)
			throw new NullPointerException("command == null");
		
		synchronized (tasks) {
			if (shutdown)
				throw new RejectedExecutionException("shutdown == true");
			
			try {
				// not a blocking call on this mutex -> free to use synchronized block
				tasks.put(command);
			} catch (InterruptedException e) {
				// Only when out of memory
			}
			
		}

	}

	@Override
	public void shutdown() {
		synchronized (tasks) {
			shutdown = true;
			
			int length = workers.length;
			
			for(int i = 0; i < tasks.remainingCapacity(); i++) {
				
			}
			
		}
		
	}
	
	
	private class Worker implements Runnable {

		private boolean shutdown;
		private Thread thread;
		
		public Worker() {
			this.shutdown = false;
			this.thread = new Thread(this);
		}
		
		@Override
		public void run() {
			while(true) {
				synchronized (thread) {
					if (shutdown)
						return;					
				}
				
				try {
					Runnable runnable = tasks.take();
					runnable.run();
				} catch (InterruptedException e) {
					//Siamo qua solo se il thread viene interrotto, ed essendo 
					//private può solo essere interrotto passando dalla shutdown del servizio
					return;
				} catch (Throwable throwable) {
					throwable.printStackTrace();
				}
			}			
		}
		
		private void start() {
			thread.start();
		}
		
		private void shutdown() {
			synchronized (thread) {
				shutdown = true;
				thread.interrupt();
			}
		}		
	}
}
