package net.davoleo.uni.examples;

public class Example01 {

	private Object mutex = new Object();

	private boolean waitInProgress = false;

	public void go() {
		waitInProgress = false;

		Thread notifier = new Thread(this::doNotify);

		Thread waiter = new Thread(this::doWait);

		notifier.start();
		waiter.start();
	}

	private void doWait() {
		System.out.println("Waiter started");

		synchronized(mutex) {
			waitInProgress = true;
			mutex.notifyAll();

			try {
				mutex.wait();
			} catch (InterruptedException e) {
				// Il thread è stato terminato dall'esterno -> Nessun problema in questo caso
			}
		}

		waitInProgress = false;

		System.out.println("Waiter terminated");
	}

	private void doNotify() {
		System.out.println("Notifier started");

		synchronized(mutex) {
			try {
				while (!waitInProgress)
					mutex.wait();

				Thread.sleep(5000);

				mutex.notifyAll();
			} catch (Throwable throwable) {
				//noop
			}
		}

		System.out.println("Notifier terminated");
	}

	public static void main(String[] args) {
		new Example01().go();
	}

}