package net.davoleo.uni.examples.ex11;

import java.util.LinkedList;
import java.util.List;

import net.davoleo.uni.aspects.SharedAspect;

public class Example11 {

	private void go( ) {
		List<Integer> list = SharedAspect.attach(new LinkedList<>());
		
		for (int i = 0; i < 10; ++i) {
			final int id = i;
			new Thread(() -> {
				for (int c = 0; c < 10000; ++c) 
					list.add(c);
				
				System.out.println("Thread " + id + " done");
			}).start();
		}
		
		try {
			Thread.sleep(5000);
			System.out.println(list.size());
		}catch (Throwable throwable) {
			//Blank
		}
		
	}
	
	public static void main(String[] args) {
		new Example11().go();
	}
}
