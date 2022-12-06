package net.davoleo.uni.examples.ex16;

import net.davoleo.uni.aspects.ReloadableAspect;
import net.davoleo.uni.aspects.ReloadableHandler;

public class Example16 {

	private void go() {
		ReloadableHandler<T> handler = ReloadableAspect.newHandler(Runnable.class, "net.davoleo.uni.examples.SimpleRelodableWorker", new String[] { "bin" });
	}
	
	public static void main(String[] args) {
		new Example16().go();
	}
}
