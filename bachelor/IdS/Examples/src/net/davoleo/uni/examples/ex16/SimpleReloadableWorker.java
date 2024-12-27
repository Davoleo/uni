package net.davoleo.uni.examples.ex16;

public class SimpleReloadableWorker implements ReloadableWorker {
	
	private WorkerDelegate delegate = new WorkerDelegate();
	
	private int version = 1;
	
	@Override
	public void run() {
		delegate.work(this);
	}
	
	@Override
	public int getVersion() {
		return version;
	}

}
