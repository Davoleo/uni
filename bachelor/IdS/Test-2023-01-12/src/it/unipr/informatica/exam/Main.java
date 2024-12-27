package it.unipr.informatica.exam;

public class Main {
	
	private static final int K = 10;
	
	public static void main(String[] args) {
		
		TemperatureSensor[] sensors = new TemperatureSensor[K];
		
		for (int i = 0; i < K; ++i) {
			sensors[i] = TemperatureSensorFactory.newTemperatureSensor();
			sensors[i].attach(Main::displaySensorValue);
			sensors[i].start();
		}
		
		try {
			Thread.sleep(60 * 1000);
		} catch (InterruptedException e) {
			System.out.println("--- Interrupted during detection ---");
			e.printStackTrace();
		}
		
		for (int i = 0; i < K; i++)
			 sensors[i].stop();
		
	}
	
	private static void displaySensorValue(TemperatureSensor sensor) {
		System.out.println("Sensor <" + sensor.getID() + ">: " + sensor.getTemperature() + "°C");
	}

}
