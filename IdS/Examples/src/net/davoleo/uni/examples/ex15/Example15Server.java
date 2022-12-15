package net.davoleo.uni.examples.ex15;

import net.davoleo.uni.aspects.LoggingAspect;
import net.davoleo.uni.aspects.RemoteAspect;
import net.davoleo.uni.aspects.RemoteHandler;

public class Example15Server {
	private void go() {
		FileManager fileManager = new SimpleFileManager("src/net/davoleo/uni/examples");
		fileManager = LoggingAspect.attach(fileManager);
		
		try {
			RemoteHandler<FileManager> fileManagerHandler = RemoteAspect.attach(FileManager.class, fileManager, 1704);
			
			Thread.sleep(60000);
			
			fileManagerHandler.shutdown();
		} catch (Throwable throwable) {
			throwable.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		new Example15Server().go();
	}
}
