package net.davoleo.uni.examples.ex14;

import net.davoleo.uni.aspects.ActiveAspect;
import net.davoleo.uni.aspects.ActiveHandler;
import net.davoleo.uni.concurrent.Future;
import net.davoleo.uni.examples.ex05.ResourceContent;

public class Example14 {
	
	private void process(ResourceContent content) {
		System.out.println("Downloaded " + content.getData().length + " bytes from " + content.getURL());
	}
	
	private void go() {
		DownloadManager downloadManager = new SimpleDownloadManager();
		
		ActiveHandler<ActiveDownloadManager> downloadManagerHandler = ActiveAspect.attach(ActiveDownloadManager.class, downloadManager);
		
		//We obtain the active object [handled via proxy]
		ActiveDownloadManager activeDownloadManager = downloadManagerHandler.get();
		
		Future<ResourceContent> future = activeDownloadManager.download("https://www.google.it");
		
		try {
			ResourceContent content = future.get();
			process(content);
		} catch (Throwable throwable) {
			throwable.printStackTrace();
		}
		
		downloadManagerHandler.shutdown();
	}
	
	public static void main(String[] args) {
		new Example14().go();
	}

}
