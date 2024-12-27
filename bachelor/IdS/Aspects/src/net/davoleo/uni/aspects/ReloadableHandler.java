package net.davoleo.uni.aspects;

public interface ReloadableHandler<T> {

	T newInstance() throws ClassNotFoundException, IllegalAccessException, InstantiationException;
	
	Class<T> loadClass() throws ClassNotFoundException;
}
