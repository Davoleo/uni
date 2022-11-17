package net.davoleo.uni.examples;

import net.davoleo.uni.concurrent.BlockingQueue;
import net.davoleo.uni.concurrent.LinkedBlockingQueue;

public class Example02 {
	
	public void go() {
		BlockingQueue<String> queue = new LinkedBlockingQueue<>();
		
		for (int i = 0; i < 5; i++) {
			Consumer consumer = new Consumer(i, queue);
			new Thread(consumer).start();
		}
		
		for (int i = 0; i < 5; i++) {
			Producer producer = new Producer(i, queue);
			new Thread(producer).start();
		}
	}
	
	public static void main(String[] args) {
		new Example02().go();
	}

}
