package net.davoleo.uni.examples.ex15;

import java.io.IOException;

public interface FileManager {
	public String[] listFileNames(String folderName) throws IOException;
	public byte[] getFile(String path) throws IOException;
}
