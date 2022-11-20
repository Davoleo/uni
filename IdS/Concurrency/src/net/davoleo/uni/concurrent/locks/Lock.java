package net.davoleo.uni.concurrent.locks;

public interface Lock {
	
	void lock() throws InterruptedException;
	
	void unlock();
	
	Condition newCondition();

}
