package it.unipr.informatica.exam;

import java.util.List;
import java.util.Random;

public class Actor {
	
	private static final Random random = new Random();

	private final int id;
	private final List<Actor> allActors;
	private final List<Resource> allResources;
	
	private final Thread workingThread;
	
	public Actor(int id, List<Actor> actors, List<Resource> resources) {
		this.id = id;
		this.allActors = actors;
		this.allResources = resources;
		
		workingThread = new Thread(this::mainCycle);
		workingThread.start();
	}
	
	public void deliver(Message message) {
		
		if (message.getValue() <= 0)
			return;
		
		System.out.println("Actor n" + id + " Received message with value: " + message.getValue() + " about");
		synchronized (this) {
			getAnotherRandomActor().deliver(message.decremented());
		}
	}
	
	private Actor getAnotherRandomActor() {
		int newActor;
		do {
			newActor = random.nextInt(allActors.size());
		} while (newActor != id);

//		int newActor = random.nextInt(allActors.size()-1);
//
//		if (newActor >= id)
//			newActor++;

		return allActors.get(newActor);
	}

	public void stop() {
		workingThread.interrupt();
	}
	
	private void mainCycle() {
		final int maxResources = 10; 
		
		while (true) {
			//0..9 resources
			int resCount = random.nextInt(maxResources);
			
			List<Resource> myResources = allResources.subList(id*maxResources, id*maxResources + resCount);
			int sum = 0; 
			System.out.println("Actor n" + id + " will use resources: (" + id*maxResources + ".." + (id*maxResources + resCount) + ")");
			
			try {
				for (Resource resource : myResources) {
					resource.acquire();
					sum += resource.use();
				}
				
				Thread.sleep(sum);
				
				myResources.forEach(Resource::release);
				getAnotherRandomActor().deliver(new Message(sum));
			}
			catch (Throwable e) {
				//If thread got interrupted -> return from the mainCycle
				if (e instanceof InterruptedException) {
					System.err.println("Thread n°" + id + " was terminated!");
					return;
				}
				else
					System.err.println("Thread n°" + id + " catched an exception while managing resource in: (" + id*maxResources + ".." + (id*maxResources+resCount) + ")");
			}
		}
	}
}
