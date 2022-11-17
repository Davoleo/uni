package net.davoleo.uni.concurrent;

import net.davoleo.uni.concurrent.locks.Condition;
import net.davoleo.uni.concurrent.locks.Lock;
import net.davoleo.uni.concurrent.locks.ReentrantLock;

public final class ArrayBlockingQueue<E> implements BlockingQueue<E> {
	
	//Can't create an array of type E [because of type erasure]
	protected Object[] queue;
	
	protected int in, out;
	
	protected int count, size;
	
	private Lock lock;
	
	private Condition isNotEmpty, isNotFull;
	
	public ArrayBlockingQueue(int size) {
		if (size < 1) 
			throw new IllegalArgumentException("size < 1");
		
		this.size = size;
		this.queue = new Object[size];
		this.in = 0;
		this.out = 0;
		this.count = 0;
		this.lock = new ReentrantLock();
		this.isNotEmpty = lock.newCondition();
		this.isNotFull = lock.newCondition();
	}

	@Override
	public E take() throws InterruptedException {
		try {
			lock.lock();
			
			while (count == 0)
				isNotEmpty.await();
			
			@SuppressWarnings("unchecked")
			E result = (E) queue[out];
			
			queue[out] = null;
			--count;
			out = (out + 1) % size;
			
			isNotFull.signal();
			return result;
		}
		finally {
			lock.unlock();
		}
	}

	@Override
	public void put(E element) throws InterruptedException {
		try {
			lock.lock();
			
			while(count == size) 
				isNotFull.await();
			
			queue[in] = element;
			
			++count;
			
			in = (in + 1) % size;
			
			isNotEmpty.signal();
		}
		finally {
			lock.unlock();
		}
		
	}

	@Override
	public int remainingCapacity() {
		lock.lock();
		
		int result = size - count;
		
		lock.unlock();
		
		return result;
	}

	@Override
	public boolean isEmpty() {
		boolean result;
		
		lock.lock();
		
		result = count == 0;
		
		lock.unlock();
		
		return result;
	}

	@Override
	public void clear() {
		lock.lock();
		in =  out = count = 0;
		//Free array -> allow GC to clean up
		queue = new Object[size];
		
		isNotFull.signalAll();
		lock.unlock();
	}
}
