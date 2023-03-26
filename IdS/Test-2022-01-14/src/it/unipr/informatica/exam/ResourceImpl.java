package it.unipr.informatica.exam;

import java.util.Random;

public class ResourceImpl implements Resource {
	
	private static final Random RANDOM = new Random();
	
	private final int id;
	
	private volatile boolean acquired;

	public ResourceImpl(int id) {
		this.id = id;
		this.acquired = false;
	}
	
	@Override
	public int getID() {
		return id;
	}
	
	public synchronized boolean isAcquired() {
		return acquired;
	}

	@Override
	public synchronized int use() {
		if (!acquired)
			throw new IllegalStateException("Resource was used when not acquired!");
		
		return RANDOM.nextInt(id, id+100);
	}
	
	public void acquire() {
		this.acquired = true;
	}

	@Override
	public void release() {
		acquired = false;
	}

}
