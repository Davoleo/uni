package it.unipr.informatica.exam;

import java.util.Random;

public class ResourceImpl implements Resource {
	
	private static final Random RANDOM = new Random();
	private static final int FREE = -1;
	
	private final int id;
	
	private int ownerId;

	public ResourceImpl(int id) {
		this.id = id;
		this.ownerId = FREE;
	}
	
	@Override
	public int getID() {
		return id;
	}
	
	public synchronized boolean isAcquired() {
		return ownerId != FREE;
	}

	@Override
	public synchronized int use() {
		if (ownerId == FREE)
			throw new IllegalStateException("Resource" + id + " was used when not acquired!");
		
		return RANDOM.nextInt(id, id+100);
	}

	public synchronized void acquire(int worker) {
		if (ownerId != FREE)
			throw new IllegalStateException("Worker" + worker + " is trying to acquire busy resource (id:" + id + ")! current owner: Worker" + ownerId);
		this.ownerId = worker;
	}

	@Override
	public synchronized void release() {
		ownerId = FREE;
	}

}
