package net.davoleo.uni.examples.ex15;

public class Example15Client {
	private void go() {
		try {
			FileManager fileManager = RemoteAspect.connect(FileManager.class, "localhost", 1704);
			String[] fileNames = fileManager.listFileNames(".");
			for (String fileName : fileNames) {
				byte[] file = fileManager.getFile(fileName);
				System.out.println("Received this shit: " + file.length + "bytes for file " + fileName);
			}
			
			fileManager.getFile("missingFile");
		} catch (Throwable throwable) {
			throwable.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		new Example15Client().go();
	}
}
