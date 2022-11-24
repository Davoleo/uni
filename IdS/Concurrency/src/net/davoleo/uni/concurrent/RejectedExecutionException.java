package net.davoleo.uni.concurrent;

public class RejectedExecutionException extends RuntimeException {
	
	private static final long serialVersionUID = 6932667938092953637L;

	//Costruttore vuoto: motivi storici, Serializable ne aveva bisogno prima
	
	//Messaggio che viene stampato insieme allo stacktrace
	public RejectedExecutionException(String message) {
		super(message);
	}

}
