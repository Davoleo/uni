package it.unipr.informatica.exam;

public class ResourceManagerImpl implements ResourceManager {
	
	private final boolean[] flags;
	
	public ResourceManagerImpl(int resCount) {
		this.flags = new boolean[resCount];
		for (int i = 0; i < resCount; i++) {
			flags[i] = false;
		}
	}

	@Override
	public synchronized void acquireResources(int i, int j) {
		
		try {
			while (flags[i] || flags[j])
				wait();
			
			flags[i] = true;
			flags[j] = true;
		} catch (InterruptedException e) {
			throw new RuntimeException("Interrupted while acquiring resources: " + i + ", " + j);
		}
	}

	@Override
	public synchronized void freeResources(int i, int j) {
		flags[i] = false;
		flags[j] = false;
		notifyAll();
	}
}
