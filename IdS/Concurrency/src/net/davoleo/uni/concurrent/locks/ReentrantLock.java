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
	public void lock() {
		if (counter < 0)
			throw new IllegalMonitorStateException("counter < 0");

		Thread currentThread = Thread.currentThread();

		synchronized (mutex) {

			//while owner exists and is different from the current thread -> thread goes in locked state
			while (owner != null && owner != currentThread) {
				try {
					mutex.wait();
				}
				catch (InterruptedException e) {
					throw new IllegalMonitorStateException("interrupted");
				}
			}

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
		private final Object condition;

		private InnerCondition() {
			this.condition = new Object();
		}
		
		@Override
		public void await() throws InterruptedException {
			//release the lock [we're the only ones who can do it]
			//to allow other threads to optionally acquire it
			unlock();

			//Wait for the condition to be signaled
			synchronized (condition) {
				condition.wait();
			}

			//We reach this point if the condition was signaled -> we then acquire the lock to do whatever we need to
			lock();
		}

		@Override
		public void signal() {
			synchronized (mutex) {
				if (owner != Thread.currentThread())
					throw new IllegalMonitorStateException("owner != Thread.currentThread()");
			}
			
			synchronized (condition) {
				condition.notify();
			}
			
		}

		@Override
		public void signalAll() {
			synchronized (mutex) {
				if (owner != Thread.currentThread())
					throw new IllegalMonitorStateException();
			}
			
			synchronized (condition) {
				condition.notifyAll();
			}
			
		}
		
	}	
}
