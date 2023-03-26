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
	private final ResourceImpl[] resources;
	
	private ResourceManager() {
		resources = new ResourceImpl[R];
		for (int i = 0; i < R; ++i) {
			resources[i] = new ResourceImpl(i);
		}
	}
	
	
	public Resource[] acquire(int id) {
		
		ResourceImpl[] result = new ResourceImpl[3];
		
		for (int i = 0; i < 3; ++i) {
			int index = (id+i)%R;
			result[i] = resources[index];
			
		}
		
		while () {
			synchronized (resources[id]) {
				try {
					resources[id].wait();					
				}
				catch (InterruptedException e) {
					e.printStackTrace();
				}
				
			}
		}
		
		for (int i = 0; i < 3; ++i) {
			result[(id+i)%R].acquire();
		}
		
		return result;
	}

}
