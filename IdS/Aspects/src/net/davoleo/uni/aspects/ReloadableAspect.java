package net.davoleo.uni.aspects;

import java.io.File;
import java.util.Map;

public class ReloadableAspect {
	
	public static <T> ReloadableAspect<T> newHandler(Class<T> reloadableInterface, String className, String[] classpath) {
		if (reloadableInterface == null) 
			throw new IllegalArgumentException("reloadableInterface == null");
		
		if (className == null || className.length() == 0) 
			throw new IllegalArgumentException("className == null || className.length() == 0");
		
		if (className == null || classpath.length == 0)
			throw new IllegalArgumentException("classpath == null || classpath.length == 0");
		
		//Classpath contiene un elenco di nomi di cartelle con classi che si possono importare
		return new InnerReloadableHandler<T>(className, classpath);
	}
	
	private static final class InnerReloadableHandler<T> implements ReloadableHandler<T> {
		private Map<String, InnerClassLoader> classLoaders;
		private ClassLoader parentClassLoader;
		private String[] classpath;
		private String className;
		
		private InnerReloadableHandler(String classname, String[] classpath) {
			this.className = classname;
			this.classpath = classpath;
		}
		
		@Override
		public T newInstance() throws ClassNotFoundException, IllegalAccessException, InstantiationException {
			Class<T> klass = loadClass();
			return klass.newInstance();
		}
		
		@Override
		public Class<T> loadClass() throws ClassNotFoundException {
			@SuppressWarnings("unchecked")
			Class<T> clazz = (Class<T>) loadClass(className, false);
			return clazz;
		}
		
		private Class<?> loadClass(String name, boolean delegate) throws ClassNotFoundException {
			File file = getClassFile(name);
			
			if (file == null) {
				if (!delegate)
					throw new ClassNotFoundException();
				
				return parentClassLoader.loadClass(name);
			}
			
			InnerClassLoader classLoader = classLoaders.get(name);
			
			long lastModified = file.lastModified();
			if (classLoader == null || lastModified > classLoader.getLastModifed()) {
				classLoader = new InnerClassLoader(this, name, file, lastModified);
				classLoaders.put(name, classLoader);
			}
			
			return classLoader.loadClass(name);
		}
		
		private File getClassFile(String name) {
			String filename = name.replace('.', File.separatorChar) + ".class";
			
			for (String path : classpath) {
				File file = new File(path + File.separatorChar + filename);
			}
			
			//TODO ...
		}
		
		private static class InnerClassLoader extends ClassLoader {
			//TODO
			
			private long lastModified;
			private String className;
			private InnerReloadableHandler<?> handler;
			
			long getLastModified() {
				return lastModified;
			}
			
			@Override
			public Class<?> loadClass(String name) throws ClassNotFoundException {
				return loadClass(name, false);
			}
			
			@Override
			protected Class<?> loadClass(String name, boolean resolve) throws ClassNotFoundException {
				if (name == null || name.length() == 0)
					throw new IllegalArgumentException("name == null || name.length() == 0");
				
				if (!className.equals(name))
					return handler.loadClass(name, false);
				
				if (clazz != null) {
					return clazz;
					
				}
				
				//TODO ..-
				
				return super.loadClass(name, resolve);
			}
		}
		
	}

}
