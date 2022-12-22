package it.unipr.informatica.exercise;

public interface Resource {
	int getID();
	int use();
	void release();
}
