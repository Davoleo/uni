package it.unipr.informatica.exam;

public class Waiter extends Thread {
	
	private final Barrier barrier;
	private int count;
	
	public Waiter(Barrier barrier) {
		this.barrier = barrier;
		count = 1;
	}

	@Override
	public void run() {
		while (true) {
			try {
				barrier.await();
				System.out.println(count++);
			} catch (InterruptedException e) {
				System.err.println("Waiter interrupted while waiting for barrier to unlock.");
				return;
			}
		}
	}
}
