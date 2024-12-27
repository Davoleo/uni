package it.unipr.informatica.exam;

public class SlaveManager {
	
	private static SlaveManager instance;
	
	public static SlaveManager get() {
		if (instance == null) {
			instance = new SlaveManager();
		}
		
		return instance;
	}
	
	private SlaveManager() {
	}
	
	public Slave newDummySlave() {
		return new DummySlave();
	}
	
}
