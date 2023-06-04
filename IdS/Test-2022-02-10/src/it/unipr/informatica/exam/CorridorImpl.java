package it.unipr.informatica.exam;

public class CorridorImpl implements Corridor {
	
	public static final int K = 5;
	
	public Thread checkerThread;
	public int count;
	
	public CorridorImpl() {
		this.count = 0;
		this.checkerThread = new Thread(this::checkNotify);
		this.checkerThread.start();
		System.out.println("checkerThread is " + checkerThread.getName());
	}
	
	public void close() {
		checkerThread.interrupt();
	}
	
	private void checkNotify() {
		while (true) {
			synchronized (this) {
				if (count >= K) {
					for (int i = 0; i < K; i++)
						this.notify();
				}
			}
			
			synchronized (checkerThread) {
				try {
					checkerThread.wait();
				} catch (InterruptedException e) {
					System.err.println("checkerThread interrupted!");
					return;
				}
			}
		}
	}

	@Override
	public synchronized void enter() {
		
		System.out.println("Thread" + Thread.currentThread().getId() + " Entering Corridor");
		
		//Notify checker thread to do its waiting count check
		synchronized (checkerThread) {
			checkerThread.notify();			
		}
		
		count++;
		
		try {
			this.wait();
		} catch (InterruptedException e) {
			System.err.println("Thread " + Thread.currentThread().getId() + " Interrupted while waiting in corridor");
		}
	}

	@Override
	public void exit() {
		System.out.println("Thread" + Thread.currentThread().getId() + " Exiting Corridor");
	}
}
