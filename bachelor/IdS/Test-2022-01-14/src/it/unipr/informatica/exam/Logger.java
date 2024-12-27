package it.unipr.informatica.exam;

public class Logger {

	private static volatile Logger instance;
	
	public static Logger get() {
		if (instance == null) {
			synchronized (Logger.class) {
				if (instance == null) 
					instance = new Logger();
			}
		}
		
		return instance;
	}
	
	private Logger() {
		//Nothing to initialize here
	}
	
	public void useAndPrint(Resource r1, Resource r2, Resource r3) {
		int t = r1.use() + r2.use() + r3.use();
		System.out.println(t);
	}
	
}
