package it.unipr.informatica.exam;

import static it.unipr.informatica.exam.Main.R;

public class ResourceManager {
	
	private static volatile ResourceManager instance;
	public static ResourceManager get() {
		if (instance == null) {
			synchronized (ResourceManager.class) {
				if (instance == null)
					instance = new ResourceManager();
			}
		}
		
		return instance;
	}
	
	private final ResourceImpl[] allResources;
	private ResourceManager() {
		allResources = new ResourceImpl[R];
		for (int i=0; i < R; i++) {
			allResources[i] = new ResourceImpl(i);
		}
	}
	
	public Resource[] acquire(int id) {
		synchronized (allResources) {
			ResourceImpl[] r = new ResourceImpl[3];
			r[0] = (ResourceImpl) allResources[id];
			r[1] = (ResourceImpl) allResources[(id+4) % R];
			r[2] = (ResourceImpl) allResources[(id+8) % R];
			
			while(!r[0].isFree() || !r[1].isFree() || !r[2].isFree()) {
				try {
					allResources.wait();
				} catch (InterruptedException e) {
					throw new RuntimeException("ResourceManager out of time while waiting for resources: " + r[0].getID() + ", " + r[1].getID() + ", " + r[2].getID());
				}
			}
			
			r[0].setFree(false);
			r[1].setFree(false);
			r[2].setFree(false);
			
			System.out.println(Thread.currentThread().getName() + ", resources " + r[0].getID() + '-' +  r[1].getID() + '-' + r[2].getID() + " acquired");
			
			return r;
		}
	}

}
