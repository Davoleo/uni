package net.davoleo.uni.aspects;

public interface ReloadableHandler<T> {

	public T newInstance() throws ClassNotFoundException, IllegalAccessException, InstantiationException;
	
	public Class<T> loadClass() throws ClassNotFoundException;
}
