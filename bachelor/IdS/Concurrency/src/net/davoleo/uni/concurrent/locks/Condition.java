package net.davoleo.uni.concurrent.locks;

public interface Condition {
	void await() throws InterruptedException;
	
	void signal();
	
	void signalAll();

}
