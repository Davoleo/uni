package net.davoleo.uni.examples.ex05;

import net.davoleo.uni.concurrent.ExecutorService;
import net.davoleo.uni.concurrent.Executors;
import net.davoleo.uni.concurrent.Future;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;

public class DownloadManager {
	
	private static final int BUFFER_SIZE = 1024;
	
	private final ExecutorService executorService;
	
	public DownloadManager(int connection) {
		if (connection < 1) 
			throw new IllegalArgumentException("connections < 1");
		
		this.executorService = Executors.newFixedThreadPool(connection);
	}
	
	public void shutdown() {
		executorService.shutdown();
	}
	
	public Future<ResourceContent> download(String url) {
		if (url == null) {
			throw new IllegalArgumentException("url == null");
		}
		
		return executorService.submit(() -> downloadResourceContent(url));
	}
	
	private ResourceContent downloadResourceContent(String url) throws IOException {
		try (InputStream inputStream = new URL(url).openStream();
				BufferedInputStream bufferedInputStream = new BufferedInputStream(inputStream);
				ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {

			byte[] buffer = new byte[BUFFER_SIZE];
			
			int read = bufferedInputStream.read(buffer);
			
			while (read >= 0) {
				outputStream.write(buffer, 0, read);
				read = bufferedInputStream.read(buffer);
			}
			
			byte[] data = outputStream.toByteArray();
			
			return new ResourceContent(url, data);
		}
	}

}
