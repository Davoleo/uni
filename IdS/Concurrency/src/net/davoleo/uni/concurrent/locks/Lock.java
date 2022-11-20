package net.davoleo.uni.concurrent.locks;

public interface Lock {
	
	void lock();
	
	void unlock();
	
	Condition newCondition();

}
