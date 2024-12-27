package it.unipr.informatica.exercise;

public class Exercise1 {
	
	private static void work() {
		try {
			int k = (int) Math.floor(Math.random() * 100);
			Thread.sleep(5000+k*10);
			System.out.println(Thread.currentThread().getName() + " " + k);
		} 
		catch (Throwable throwable) {
			// Interrupted sleep
		}
	}
	
	public static void main(String[] args) {
		Launcher launcher = new LauncherImpl();
		MonitorSet monitorSet = new MonitorSetImpl();
		
		int n = 5;
		for (int i = 0; i < n; i++) {
			Monitor monitor = launcher.launch(Exercise1::work);
			monitorSet.add(monitor);
		}
		
		for (int i = 0; i < n; i++) {
			try {
				monitorSet.await();
			}
			catch (Throwable throwable) {
				throwable.printStackTrace();
			}
		}
	}
}
