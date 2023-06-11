package it.unipr.informatica.exam;

public class ResourceImpl implements Resource {
	
	private final int id;
	private boolean free;
	
	public ResourceImpl(int id) {
		this.id = id;
		this.free = true;
	}

	@Override
	public int getID() {
		return id;
	}

	@Override
	public int use() {
		return (int) (Math.random()*(id+99)+id);
	}

	@Override
	public void release() {
		synchronized (this) {
			free = true;
			this.notify();
			
			//System.out.println(Thread.currentThread().getName() + ",resource " + getID() + " released");
		}
	}
	
	public boolean isFree() {
		synchronized (this) {
			return free;
		}
	}
	
	public void setFree(boolean free) {
		synchronized (this) {
			this.free = free;
		}
	}

}
