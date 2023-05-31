package it.unipr.informatica.exam;

import java.util.LinkedHashSet;
import java.util.Random;
import java.util.Set;

public class TemperatureSensorImpl implements TemperatureSensor {
	
	private static final Random RANDOM = new Random();
	
	private final int sensorID;
	private double temperature;
	
	//Threads
	private final Thread sensorThread;
	private final SimpleThreadPool threadPool;
	
	private final Set<TemperatureObserver> observers;
	
	public TemperatureSensorImpl(int sensorID) {
		this.sensorID = sensorID;
		this.temperature = 0D;
	
		this.sensorThread = new Thread(this::detectTemperature);
		this.threadPool = new SimpleThreadPool(10);
		
		this.observers = new LinkedHashSet<>();
	}

	@Override
	public int getID() {
		return sensorID;
	}

	@Override
	public synchronized double getTemperature() {
		return temperature;
	}
	
	public synchronized void setTemperature(double temperature) {
		this.temperature = temperature;
	}

	@Override
	public void start() {
		this.sensorThread.start();
	}

	@Override
	public void stop() {
		this.sensorThread.interrupt();
		this.threadPool.shutdown();
	}

	@Override
	public void attach(TemperatureObserver observer) {
		observers.add(observer);
	}

	@Override
	public void detach(TemperatureObserver observer) {
		observers.remove(observer);
	}
	
	
	private void detectTemperature() {
		
		while (true) {
			try {
				double detected= RANDOM.nextDouble(100);
				setTemperature(detected);
				for (TemperatureObserver observer : observers) {
					threadPool.execute(() -> observer.update(this));
				}
				
				Thread.sleep(1000);	
			}
			catch (InterruptedException e) {
				//Interrupt from the external world -> stop detecting
				System.out.println("Sensor Thread <" + getID() + ">: Interrupted");
				break;
			}
		}
		
	}
}
