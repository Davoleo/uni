package net.davoleo.uni.examples.ex16;

import net.davoleo.uni.aspects.ReloadableAspect;
import net.davoleo.uni.aspects.ReloadableHandler;

public class Example16 {

	private void go() {
		ReloadableHandler<Runnable> handler = ReloadableAspect.newHandler(
				Runnable.class, 
				"net.davoleo.uni.examples.ex16.SimpleReloadableWorker", 
				new String[] { "bin" }
		);
		
		for (int i = 0; i < 10; ++i) {
			try {
				Runnable worker = handler.newInstance();
				
				new Thread(worker).start();
				
				Thread.sleep(5000);
			}catch (Throwable throwable) {
				throwable.printStackTrace();
			}
		}
	}
	
	public static void main(String[] args) {
		new Example16().go();
	}
}
