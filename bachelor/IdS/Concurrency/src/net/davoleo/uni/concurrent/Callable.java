package net.davoleo.uni.concurrent;

public interface Callable<T> {
	T call() throws Exception;
}
