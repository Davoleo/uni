package net.davoleo.uni.concurrent;

public class Executors {
	
	
	public static ExecutorService newFixedThreadPool(int threadCount) {
		return new SimpleThreadPoolExecutorService(threadCount);
	}
	
	private Executors() {
		
	}

}
