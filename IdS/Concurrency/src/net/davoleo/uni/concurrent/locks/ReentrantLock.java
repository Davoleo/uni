package net.davoleo.uni.concurrent.locks;

public class ReentrantLock implements Lock {

	private Object mutex;
	
	@Override
	public void lock() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void unlock() {
		// TODO Auto-generated method stub
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
