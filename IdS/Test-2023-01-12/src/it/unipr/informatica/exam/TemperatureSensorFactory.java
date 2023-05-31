package it.unipr.informatica.exam;

public class TemperatureSensorFactory {
	
	private static int sensorCount = 2;
	
	public static TemperatureSensor newTemperatureSensor() {
		return new TemperatureSensorImpl(sensorCount++);
	}
}
