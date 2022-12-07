package net.davoleo.uni.aspects;

import java.io.Serializable;

public interface RemoteRequest extends Serializable {

	String getMethodName();
	String[] getParameterTypeNames();
	Object[] getArguments();
	
}
