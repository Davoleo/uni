package net.davoleo.uni.aspects;

import java.io.IOException;

public interface PersistentHandler<T> {
	
	T get();
	
	void rollback() throws IOException;
	
	void commit() throws IOException;

}
