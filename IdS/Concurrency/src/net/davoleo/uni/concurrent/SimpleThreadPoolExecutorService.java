package net.davoleo.uni.concurrent;

//Package scope -> to avoid end user creating instances of this class directly 
class SimpleThreadPoolExecutorService implements ExecutorService {

	private final Worker[] workers;
	private final BlockingQueue<Runnable> tasks;
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
			for (Worker worker : workers) {
				worker.shutdown();
			}
		}
		
	}
	
	@Override
	public Future<?> submit(Runnable task) {
		if (task == null)
			throw new NullPointerException("task == null");
		
		
		SimpleFuture<?> future = new SimpleFuture<>();
		
		execute(() -> {
			try {
				task.run();
				future.setValue(null);
			} catch (Throwable throwable) {
				future.setException(throwable);
			}
		});
		
		return future;
	}
	
	@Override
	public void submit(Runnable task, Callback<?> callback) {
		if (task == null)
			throw new NullPointerException("task == null");
		
		if (callback == null)
			throw new NullPointerException("callback == null");
		
		execute(() -> {
			try {
				task.run();
				callback.onSuccess(null);
			} catch (Throwable throwable) {
				callback.onFailure(throwable);
			}
		});
	}
	
	@Override
	public <T> Future<T> submit(Callable<T> task) {
		if (task == null)
			throw new NullPointerException("task == null");
		
		
		SimpleFuture<T> future = new SimpleFuture<>();
		
		execute(() -> {
			try {
				T result = task.call();
				future.setValue(result);
			} catch (Throwable throwable) {
				future.setException(throwable);
			}
		});
		
		return future;
	}
	
	@Override
	public <T> void submit(Callable<T> task, Callback<T> callback) {
		if (task == null)
			throw new NullPointerException("task == null");
		
		if (callback == null)
			throw new NullPointerException("callback == null");
		
		execute(() -> {
			try {
				T result = task.call();
				callback.onSuccess(result);
			} catch (Throwable throwable) {
				callback.onFailure(throwable);
			}
		});
	}
	
	
	private class Worker implements Runnable {

		private boolean shutdown;
		private final Thread thread;
		
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
