package net.davoleo.uni.examples.ex04;

import java.util.concurrent.atomic.AtomicReference;
import java.util.function.UnaryOperator;

public class Example04 {
	private void go() {
		AtomicReference<Integer> counter = new AtomicReference<>(1);
		
		Incrementer incrementer = new Incrementer();
		
		int i = counter.get();
		while (i <= 10) {
			System.out.println(i);
			i = counter.updateAndGet(incrementer);
		}
		
		
		UnaryOperator<Integer> incrementerAnony = new UnaryOperator<Integer>() {
			@Override
			public Integer apply(Integer t) {
				return t+1;
			}
		};
		
		while (i <= 20) {
			System.out.println(i);
			counter.getAndUpdate(incrementerAnony);
		}
		
		while (i <= 30) {
			System.out.println(i);
			i = counter.updateAndGet(t -> t+1);
		}
	}
	
	public static void main(String[] args) {
		new Example04().go();
	}
	
	private static class Incrementer implements UnaryOperator<Integer> {
		@Override
		public Integer apply(Integer t) {
			return t+1;
		}
	}
}
