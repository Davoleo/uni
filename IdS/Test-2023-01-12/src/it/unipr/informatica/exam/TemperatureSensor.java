package it.unipr.informatica.exam;

public interface TemperatureSensor {
	
	public int getID();
	
	public double getTemperature();
	
	public void start();
	public void stop();

	public void attach(TemperatureObserver observer);
	public void detach(TemperatureObserver observer);
}
