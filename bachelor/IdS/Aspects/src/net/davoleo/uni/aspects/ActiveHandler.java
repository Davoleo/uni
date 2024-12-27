package net.davoleo.uni.aspects;

public interface ActiveHandler<T extends Active<?>> {

	T get();
	
	void shutdown();
	
}
