package net.davoleo.uni.concurrent;

public interface ExecutorService extends Executor {

	void shutdown();
	
	//Wildcard: can return any future type
	// -> Will actually just return null since we're executing a Runnable
	Future<?> submit(Runnable task);
	
	void submit(Runnable task, Callback<?> callback);
	
	<T> Future<T> submit(Callable<T> task);
	
	<T> void submit(Callable<T> task, Callback<T> callback);
}
