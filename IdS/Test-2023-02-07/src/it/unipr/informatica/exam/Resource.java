package it.unipr.informatica.exam;

public interface Resource {
	public int getID();
	public void acquire() throws InterruptedException;
	public void release();
	public int use();
}
