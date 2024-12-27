package it.unipr.informatica.exam;

import java.util.ArrayList;
import java.util.List;

public class Main {
	private static final int N = 10;
	private static final int M = 100;

	public static void main(String[] args) {
		ActorResourceFactory factory = ActorResourceFactory.getInstance();
		
		List<Resource> resources = new ArrayList<>(M);
		for (int i = 0; i < M; i++) {
			resources.add(factory.createResource());
		}
		
		List<Actor> actors = new ArrayList<>(N);
		for (int i = 0; i < N; i++) {
			actors.add(factory.createActor(i, actors, resources));
		}
		
		try {
			Thread.sleep(1000 * 10);
			actors.forEach(Actor::stop);
		} catch (InterruptedException e) {
			System.out.println("interrupted!");
			e.printStackTrace();
		}
	}
	
}
