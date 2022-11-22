package net.davoleo.uni.concurrent;

public class RejectedExecutionException extends RuntimeException {
	
	private static final long serialVersionUID = 6932667938092953637L;

	public RejectedExecutionException(String message) {
		super(message);
	}

}
