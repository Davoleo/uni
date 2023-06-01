package it.unipr.informatica.exam;

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
		for (int i = 0; i < R; ++i) {
			allResources[i] = new ResourceImpl(i);
		}
	}
	
	
	public Resource[] acquire(int id) throws InterruptedException {
		
		ResourceImpl[] myResources = new ResourceImpl[3];
		
		for (int i = 0; i < 3; ++i) {
			int index = (id+i)%R;
			myResources[i] = allResources[index];
		}
		
		while (myResources[0].isAcquired() || myResources[1].isAcquired() || myResources[2].isAcquired()) {
			synchronized (myResources[0]) {
				myResources[0].wait();
			}
		}
		
		for (ResourceImpl resource : myResources) 
			resource.acquire();
		
		System.out.println("Worker" + id + ": acquired resources [" + id + "-" + (id+1)%R + "-" + (id+2)%R + ']');
		
		return myResources;
	}

}
