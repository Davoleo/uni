package it.unipr.informatica.exam;

import it.unipr.informatica.exam.concurrent.SimpleLock;

class ResourceImpl implements Resource {
	
	private static int resourceCount;
	private final int id;
	private final SimpleLock lock;
	
	public ResourceImpl() {
		this.id = resourceCount++;
		this.lock = new SimpleLock();	
	}

	@Override
	public int getID() {
		return id;
	}

	@Override
	public void acquire() throws InterruptedException {
		lock.lock();
		//System.out.println("Thread " + Thread.currentThread().getName() + " Acquired Resource n" + this.id);
	}

	@Override
	public void release() {
		lock.unlock();
	}

	@Override
	public int use() {
		if (!lock.isCurrentThreadOwner())
			throw new IllegalStateException("You're not the owner of this resource!");
		return (int) Math.floor(Math.random() * 10);
	}

}
