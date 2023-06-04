package it.unipr.informatica.exam;

public class Main {
	public static void main(String[] args) {
		WorkerManager workerManager = WorkerManager.getInstance();
		Worker[] workers = workerManager.createWorkers();
		
		for (Worker worker : workers) {
			new Thread(() -> {
				worker.execute();
				System.out.println("Done " + Thread.currentThread().getId());
			}).start();
		}
		
		try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		workerManager.closeCorridor();
	}
}
