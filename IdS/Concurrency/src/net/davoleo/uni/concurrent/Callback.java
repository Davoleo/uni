package net.davoleo.uni.concurrent;

public interface Callback<T> {
	void onSuccess(T result);
	
	default void onFailure(Throwable throwable) {
		throwable.printStackTrace();
	}
}
