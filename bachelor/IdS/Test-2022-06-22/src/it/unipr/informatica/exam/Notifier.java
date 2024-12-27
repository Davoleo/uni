package it.unipr.informatica.exam;

public class Notifier extends Thread {
	
	private final Object object;
	
	public Notifier(Object object) {
		this.object = object;
	}
	
	@Override
	public void run() {
		while (true) {
			int millis = (int) (Math.random() * 100);
			
			try {
				Thread.sleep(millis);
				
				synchronized (object) {
					object.notifyAll();
				}
			} catch (InterruptedException e) {
				System.err.println("Notifier" + Thread.currentThread().getId() + " interrupted.");
				return;
			}
		}
	}
	
	public Object getObject() {
		return object;
	}

}
