package it.unipr.informatica.exercise;

public interface Monitor {
	void await() throws InterruptedException;
}
