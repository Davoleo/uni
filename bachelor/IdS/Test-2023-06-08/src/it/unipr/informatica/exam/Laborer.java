package it.unipr.informatica.exam;

public class Laborer extends Thread {
	
	public final int id;
	
	public Laborer(int id) {
		if (id < 0) 
			throw new IllegalArgumentException("id < 0!!");
		
		this.id = id;
	}

	@Override
	public void run() {	
		
		ResourceManager manager = ResourceManager.get();
		
		while (true) {
			try {
				Resource[] resources = manager.acquire(id);
				useAndPrint(resources[0], resources[1], resources[2]);
				Thread.sleep(200);
			} catch (InterruptedException e) {
				System.err.println("Laborer " + id + ": out of timer while waiting");
				return;
			} catch (RuntimeException exception) {
				System.err.println(exception.getMessage());
				return;
			}
		}
	}
	
	private void useAndPrint(Resource r1, Resource r2, Resource r3) {
		int t = r1.use() + r2.use() * r3.use();
		
		System.out.println(t);
		
		r1.release();
		r2.release();
		r3.release();
	}
	
}
