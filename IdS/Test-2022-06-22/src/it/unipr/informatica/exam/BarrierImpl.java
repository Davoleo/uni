package it.unipr.informatica.exam;

import java.util.LinkedList;
import java.util.List;

public class BarrierImpl implements Barrier {
	
	private final List<Checker> subscribedObjects;
	
	public BarrierImpl() {
		this.subscribedObjects = new LinkedList<>();
	}

	@Override
	public void add(Object object) {
		Checker checker = new Checker(subscribedObjects.size() - 1, object);
		checker.start();
		this.subscribedObjects.add(checker);
	}

	@Override
	public void remove(Object object) {
		int index = -1;
		for (int i = 0; i < subscribedObjects.size(); i++) {
			if (subscribedObjects.get(i).getObject() == object) {
				index = i;
			}
		}
		if (index != -1) {
			Checker removed = this.subscribedObjects.remove(index);
			removed.interrupt();
		}
	}

	@Override
	public synchronized void await() throws InterruptedException {
		wait();
	}
	
	private class Checker extends Thread {
		private int index;
		private Object notificator;
		public Checker(int i, Object notificator) {
			this.index = i;
			this.notificator = notificator;
		}
		
		@Override
		public void run() {
			while (true) {
				synchronized (notificator) {
					try {
						notificator.wait();
					} catch (InterruptedException e) {
						System.err.println("Barrier Checker Thread n" + index + " interrupted while waiting for notification.");
						return;
					}
					
					synchronized (BarrierImpl.this) {
						BarrierImpl.this.notify();
					}
				}
			}
		}
		
		private Object getObject() {
			return notificator;
		}
	}
}