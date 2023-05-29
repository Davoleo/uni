package it.unipr.informatica.exam.concurrent;

public class SimpleLock implements Lock {

	private Thread owner;
	private int count;
	
	public SimpleLock() {
		this.owner = null;
		this.count = 0;
	}
	
	@Override
	public synchronized void lock() throws InterruptedException {
		
		while (owner != null && owner != Thread.currentThread()) {
			wait();
		}
		
		if (owner == null)
			owner = Thread.currentThread();
		
		count++;
	}

	@Override
	public synchronized void unlock() {
		if (count <= 0)
			throw new IllegalStateException("count == 0 : lock is already free!");
		
		if (owner != Thread.currentThread())
			throw new IllegalStateException("no permission to unlock other thread's lock!");
		
		count--;

		if (count == 0) {
			owner = null;
			notify();
		}
	}
	
	public synchronized boolean isCurrentThreadOwner() {
		return owner == Thread.currentThread();
	}
	
	
}
