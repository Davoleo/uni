package it.unipr.informatica.exercise;

public interface MonitorSet {
	boolean add(Monitor m);
	void await() throws InterruptedException;
}
