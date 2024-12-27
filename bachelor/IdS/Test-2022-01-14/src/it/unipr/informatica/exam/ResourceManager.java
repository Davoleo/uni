package it.unipr.informatica.exam;

import java.util.Arrays;

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
	
	
	private final int R = 9;
	private final ResourceImpl[] allResources;
	
	private ResourceManager() {
		allResources = new ResourceImpl[R];
		Arrays.setAll(allResources, ResourceImpl::new);
	}

	public ResourceImpl[] getAllResources() {
		return allResources;
	}

	/**
	 * Synchronized because otherwise every worker goes ahead and tries to acquire the resources at the beginning since they're theoretically all free
	 * Hopefully doesn't hinder parallel execution too much.
	 */
	public Resource[] acquire(int id) throws InterruptedException {
		
		ResourceImpl[] myResources = new ResourceImpl[3];
		
		for (int i = 0; i < 3; ++i) {
			int index = (id+i)%R;
			myResources[i] = allResources[index];
		}

		synchronized (myResources[0]) {
			while (myResources[0].isAcquired() || myResources[1].isAcquired() || myResources[2].isAcquired())
				myResources[0].wait();

			synchronized (allResources) {
				for (ResourceImpl resource : myResources)
					resource.acquire(id);
			}
		}
		
		System.out.println("Worker" + id + ": acquired resources [" + id + "-" + (id+1)%R + "-" + (id+2)%R + ']');
		
		return myResources;
	}
	
	/**
	 * Notify resource release to the previous 3 resources where there might be workers waiting.
	 * @param id of the resource that was released 
	 */
	public void notifyRelease(int id) {
		for(int i=0; i < 3; i++) {
			int index = (id - i + R) % R;
			synchronized (allResources[index]) {
				allResources[index].notifyAll();
			}			
		}
	}

}
