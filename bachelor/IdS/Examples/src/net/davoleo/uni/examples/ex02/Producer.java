package net.davoleo.uni.examples.ex02;

import net.davoleo.uni.concurrent.BlockingQueue;

public class Producer implements Runnable {
	
	private final int id;
	private final BlockingQueue<String> queue;
	
	public Producer(int id, BlockingQueue<String> queue) {
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
			for (int i = 0; i < 5; ++i) {
				String message = id + "/" + i;
				
				System.out.println("P" + id + " sending " + message);
				queue.put(message);
				System.out.println("P" + id + " sent " + message);
				
				Thread.sleep(100 + (int) (50 * Math.random()));
			}
		} catch (InterruptedException e) {
			System.err.println("Producer " + id + " interrupted");
		}
		
	}

}
