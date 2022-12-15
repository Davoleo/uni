package net.davoleo.uni.examples.ex15;

import java.io.IOException;

public interface FileManager {
	
	String[] listFileNames(String folderName) throws IOException;
	byte[] getFile(String path) throws IOException;
	
}
