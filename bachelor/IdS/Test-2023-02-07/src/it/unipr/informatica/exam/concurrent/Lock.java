package it.unipr.informatica.exam.concurrent;

public interface Lock {
	
	public void lock() throws InterruptedException;
	public void unlock();

}
