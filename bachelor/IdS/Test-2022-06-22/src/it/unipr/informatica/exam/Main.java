package it.unipr.informatica.exam;

import java.util.ArrayList;
import java.util.List;

public class Main {
		
	public static final int N = 50;
	public static void main(String[] args) {
		
		Barrier barrier = new BarrierImpl();
		Waiter waiter = new Waiter(barrier);
		
		waiter.start();
		
		List<Notifier> notifiers = new ArrayList<>(N);
		for (int i = 0; i < N; i++) {
			Object object = new Object();
			barrier.add(object);
			notifiers.add(new Notifier(object));
		}
		
		notifiers.forEach(Notifier::start);
		
		try {
			Thread.sleep(6000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		notifiers.forEach(notifier -> {
			notifier.interrupt();
			barrier.remove(notifier.getObject());
		});
		waiter.interrupt();
		
	}
}
