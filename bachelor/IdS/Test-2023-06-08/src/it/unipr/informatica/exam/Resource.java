package it.unipr.informatica.exam;

public interface Resource {
	public int getID();
	public int use();
	public void release();
}
