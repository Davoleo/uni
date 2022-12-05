package net.davoleo.uni.examples.ex14;

import java.io.IOException;

import net.davoleo.uni.examples.ex05.ResourceContent;

public interface DownloadManager {
	
	ResourceContent download(String url) throws IOException;

}
