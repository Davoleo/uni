package it.unipr.informatica.exam;

import java.util.List;

public abstract class ActorResourceFactory {
	
	private static ActorResourceFactory factory;
	public static ActorResourceFactory getInstance() {
		if (factory == null) {
			factory = new Impl();
		}
		
		return factory;
	}
	
	public abstract Actor createActor(int id, List<Actor> allActors, List<Resource> allResources);
	
	public abstract Resource createResource();

	private static class Impl extends ActorResourceFactory {

		@Override
		public Actor createActor(int id, List<Actor> allActors, List<Resource> allResources) {
			return new Actor(id, allActors, allResources);
		}

		@Override
		public Resource createResource() {
			return new ResourceImpl();
		}
	}
	
}
