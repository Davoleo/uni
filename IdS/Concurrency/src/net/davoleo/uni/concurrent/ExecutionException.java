package net.davoleo.uni.concurrent;

public class ExecutionException extends Exception {

	private static final long serialVersionUID = 7315782896131234420L;

	//Embeds throwable inside this exception to print information about the origin of this exception
	public ExecutionException(Throwable cause) {
		super(cause);
	}
}
