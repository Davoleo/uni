package net.davoleo.uni.examples.ex02;

import net.davoleo.uni.concurrent.BlockingQueue;

public class Consumer implements Runnable {
	
	private final int id;
	private final BlockingQueue<String> queue;
	
	public Consumer(int id, BlockingQueue<String> queue) {
		if (id < 0)
			throw new IllegalArgumentException("id < 0");
		
		if (queue == null)
			throw new IllegalArgumentException("queue == null");
		
		this.id = id;
		this.queue = queue;
	}
	
	@Override
	public void run() {
		try {
			for(int i = 0; i < 5; ++i) {
				String message = queue.take();
				System.out.println("C" + id + " received " + message);
				
				Thread.sleep(40 + (int) (100 * Math.random())); 
			}
		} catch (InterruptedException e) {
			System.err.println("Consumer " + id + " interrupted");
		}
		
	}
}
