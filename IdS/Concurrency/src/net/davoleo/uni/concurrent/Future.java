package net.davoleo.uni.concurrent;

public interface Future<T> {
	T get() throws InterruptedException, ExecutionException;
	
	boolean isDone();

}
