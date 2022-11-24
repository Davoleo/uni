package net.davoleo.uni.examples;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

public class Example05 {
	
	private void process(Future<ResourceContent> future) {
		try {
			ResourceContent content = future.get();
			System.out.println("Downloaded " + content.getData().length + " bytes from " content.getURL());
		}
		catch (ExecutionException e) {
			System.err.println("Cannot download with error " + e.getMessage());
		}
		catch (InterruptedException e) {
			System.err.println("Interrupted");
			System.exit(-1);
		}
	}
	
	private void go() {
		DownloadManager downloadManager = new DownloadManager(4);
		
		Future<ResourceContent> future1 = downloadManager.download("https:://www.google.it");
		Future<ResourceContent> future2 = downloadManager.download("https:://www.youtube.com");
		Future<ResourceContent> future3 = downloadManager.download("https:://www.amazon.it");
		Future<ResourceContent> future4 = downloadManager.download("https:://www.missingwebsite.com");
		Future<ResourceContent> future5 = downloadManager.download("https:://www.ebay.com");
		Future<ResourceContent> future6 = downloadManager.download("https:://www.unipr.it");
		
		process(future1);
		process(future2);
		process(future3);
		process(future4);
		process(future5);
		process(future6);

		downloadManager.shutdown();
	}
	
	public static void main(String[] args) {
		new Example05().go();
	}

}
