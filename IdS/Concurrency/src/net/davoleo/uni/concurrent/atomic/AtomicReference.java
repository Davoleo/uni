package net.davoleo.uni.concurrent.atomic;

import java.util.function.UnaryOperator;

public class AtomicReference<T> {
	private T value;
	
	private final Object lock;
	
	public AtomicReference() {
		this(null);
	}
	
	public AtomicReference(T value) {
		this.value = value;
		this.lock = new Object();
	}
	
	public T get() {
		synchronized (lock) {
			return value;
		}
	}
	
	public void set(T value) {
		synchronized (lock) {
			this.value = value;
		}
	}
	
	public T getAndSet(T value){
		synchronized (lock) {
			T result = this.value;
			this.value = value;
			return result;
		}
	}
	
	public T getAndUpdate(UnaryOperator<T> updateOp) {
		synchronized (lock) {
			T result = value;
			this.value = updateOp.apply(value);
			return result;
		}
	}
	
	public T updateAndGet(UnaryOperator<T> updateOp) {
		synchronized (lock) {
			this.value = updateOp.apply(value);
			return value;
		}
	}
}
