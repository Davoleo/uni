package it.unipr.informatica.exercise;

public class ResourceManager {
	
	private static final int R = 9;
	private static volatile ResourceManager instance;
	
	private InnerResource[] resources;
	private Object mutex;

	public static ResourceManager getInstance() {
		if (instance == null) {
			synchronized (ResourceManager.class) {
				if (instance == null)
					instance = new ResourceManager();
			}
		}
		
		return instance;
	}
	
	private ResourceManager() {
		this.resources = new InnerResource[R];
		
		for (int i = 0; i < R; ++i) {
			resources[i] = new InnerResource(i);
		}
		
		this.mutex = new Object();
	}
	
	public Resource[] acquire(int id) throws InterruptedException {
		
		if (id < 0 || id >= R)
			throw new IllegalArgumentException("id < 0 || id >= R");
		
		int id1 = (id+1) % R;
		int id2 = (id+2) % R;
		
		synchronized (mutex) {
			while (!resources[id].free || !resources[id1].free || !resources[id2].free)
				mutex.wait();
			
			resources[id].free = resources[id1].free = resources[id1].free = false;  
			return new Resource[] { resources[id], resources[id1], resources[id2] };
		}
	}

	
	private class InnerResource implements Resource {

		private boolean free;
		private int id;
		
		private InnerResource(int id) {
			this.free = true;
			this.id = id;
		}
		
		@Override
		public int getID() {
			return id;
		}

		@Override
		public int use() {
			synchronized (mutex) {
				if (free)
					throw new IllegalStateException("free resource");
				
				return id + (int) Math.floor(100 * Math.random());
			}
		}

		@Override
		public void release() {
			synchronized (mutex) {
				free = true;
			}
		}
		
	}
}
