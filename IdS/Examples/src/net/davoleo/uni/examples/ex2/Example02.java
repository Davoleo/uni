package net.davoleo.uni.examples.ex2;

import net.davoleo.uni.concurrent.ArrayBlockingQueue;
import net.davoleo.uni.concurrent.BlockingQueue;

public class Example02 {
	
	public void go() {
		//BlockingQueue<String> queue = new LinkedBlockingQueue<>();
		BlockingQueue<String> queue = new ArrayBlockingQueue<>(3);

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
