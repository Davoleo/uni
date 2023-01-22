package it.unipr.informatica.exam;

import java.util.HashSet;
import java.util.Random;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicReference;

public class TemperatureSensorImpl implements TemperatureSensor {
	
	private static final Random RANDOM = new Random();
	
	private final int sensorID;
	private final AtomicReference<Double> temperature;
	
	//Threads
	private final Thread sensorThread;
	private final ExecutorService threadPool;
	
	private final Set<TemperatureObserver> observers;
	
	public TemperatureSensorImpl(int sensorID) {
		this.sensorID = sensorID;
		this.temperature = new AtomicReference<>(0D);
	
		this.sensorThread = new Thread(this::detectTemperature);
		this.threadPool = Executors.newFixedThreadPool(10);
		
		this.observers = new HashSet<>();
	}

	@Override
	public int getID() {
		return sensorID;
	}

	@Override
	public double getTemperature() {
		return temperature.get();
	}

	@Override
	public void start() {
		this.sensorThread.start();
	}

	@Override
	public void stop() {
		this.sensorThread.interrupt();
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
				temperature.set(detected);
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
