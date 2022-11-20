package net.davoleo.uni.concurrent.locks;

public class ReentrantLock implements Lock {

	private Thread owner;
	private int counter;
	private final Object mutex;

	public ReentrantLock()
	{
		this.owner = null;
		this.counter = 0;
		mutex = new Object();
	}

	@Override
	public void lock() throws InterruptedException {
		if (counter < 0)
			throw new IllegalMonitorStateException("counter < 0");

		Thread currentThread = Thread.currentThread();

		synchronized (mutex) {

			//while owner exists and is different from the current thread -> thread goes in locked state
			while (owner != null && owner != currentThread)
				mutex.wait();

			if (owner == null)
				owner = currentThread;
			counter++;
		}
	}

	@Override
	public void unlock() {
		synchronized (mutex) {
			//Design choice: Lock can only be managed by the owner
			if (owner != Thread.currentThread())
				throw new IllegalMonitorStateException("owner != Thread.currentThread()");

			//Sanity Check
			if (counter <= 0)
				throw new IllegalMonitorStateException("counter <= 0");

			counter--;

			if (counter == 0) {
				owner = null;
				mutex.notify();
			}
		}
	}
	
	@Override
	public Condition newCondition() {
		return new InnerCondition();
	}
	
	private class InnerCondition implements Condition {
		private Object condition;

		private InnerCondition() {
			this.condition = new Object();
		}
		
		@Override
		public void await() throws InterruptedException {
			unlock();
			
			synchronized (condition) {
				condition.wait();
			}
			
			lock();
		}

		@Override
		public void signal() {
			synchronized (this) {
				if (owner != Thread.currentThread())
					throw new IllegalMonitorStateException("owner != Thread.currentThread()");
			}
			
			synchronized (condition) {
				condition.notify();
			}
			
		}

		@Override
		public void signalAll() {
			synchronized (this) {
				if (owner != Thread.currentThread())
					throw new IllegalMonitorStateException();
			}
			
			synchronized (condition) {
				condition.notifyAll();
			}
			
		}
		
	}	
}
