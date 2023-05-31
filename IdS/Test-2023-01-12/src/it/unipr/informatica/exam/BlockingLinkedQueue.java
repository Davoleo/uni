package it.unipr.informatica.exam;

import java.util.LinkedList;
import java.util.Queue;

public class BlockingLinkedQueue<E> {
	
	private final Queue<E> list;
	
	public BlockingLinkedQueue() {
		list = new LinkedList<>();
	}
	
	public void enqueue(E item) {
		synchronized (list) {
			list.add(item);
			list.notify();
		}
	}
	
	public E take() throws InterruptedException {
		synchronized (list) {
			while (list.isEmpty())
				list.wait();
		
			return list.remove();
		}
	}
	
	

}
