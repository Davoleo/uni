package net.davoleo.uni.aspects;

import java.io.Serializable;

public interface RemoteResponse extends Serializable {

	Object getResult();
	Throwable getException();
	
}
