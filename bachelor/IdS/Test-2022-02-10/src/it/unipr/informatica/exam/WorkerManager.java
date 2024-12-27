package it.unipr.informatica.exam;

import java.util.Arrays;

public class WorkerManager {
	
	private static final int W = 50;
	private static final WorkerManager instance = new WorkerManager();
	
	public static WorkerManager getInstance() {
		return instance;
	}
	
	private final CorridorImpl corridor;
	private WorkerManager() {
		this.corridor = new CorridorImpl();
	}
	
	public Worker[] createWorkers() {
		Worker[] workers = new Worker[W];
		Arrays.setAll(workers, (i) -> new WorkerImpl(corridor));
		return workers;
	}

	public void closeCorridor() {
		corridor.close();
	}
	
}
