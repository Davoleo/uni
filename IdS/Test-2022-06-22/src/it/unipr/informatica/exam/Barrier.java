package it.unipr.informatica.exam;

public interface Barrier {
	public void add(Object object);
	public void remove(Object object);
	public void await() throws InterruptedException;	
}
