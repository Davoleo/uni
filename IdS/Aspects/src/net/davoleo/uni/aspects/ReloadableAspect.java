package net.davoleo.uni.aspects;

import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class ReloadableAspect {
	
	public static <T> ReloadableHandler<T> newHandler(Class<T> reloadableInterface, String className, String[] classpath) {
		if (reloadableInterface == null) 
			throw new IllegalArgumentException("reloadableInterface == null");
		
		if (className == null || className.length() == 0) 
			throw new IllegalArgumentException("className == null || className.length() == 0");
		
		if (classpath == null || classpath.length == 0)
			throw new IllegalArgumentException("classpath == null || classpath.length == 0");
		
		//Classpath contiene un elenco di nomi di cartelle con classi che si possono importare
		return new InnerReloadableHandler<>(className, classpath);
	}
	
	private static final class InnerReloadableHandler<T> implements ReloadableHandler<T> {
		private Map<String, InnerClassLoader> classLoaders;
		private ClassLoader parentClassLoader;
		private String[] classpath;
		private String className;
		
		private InnerReloadableHandler(String classname, String[] classpath) {
			this.className = classname;
			this.classpath = classpath;
			this.parentClassLoader = getClass().getClassLoader();
			this.classLoaders = new HashMap<>();
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
			if (classLoader == null) {
				classLoader = new InnerClassLoader(this, name, file, lastModified);
				classLoaders.put(name, classLoader);
			} 
			else if (className.equals(name) && lastModified > classLoader.getLastModified()) {
				classLoaders.clear();
				classLoader = new InnerClassLoader(this, name, file, lastModified);
				classLoaders.put(name, classLoader);
			}
			
			return classLoader.loadClass(name);
		}
		
		private File getClassFile(String name) {
			// replace . with / or \ and append .class
			String filename = name.replace('.', File.separatorChar) + ".class";
			
			for (String path : classpath) {
				File file = new File(path + File.separatorChar + filename);
				
				if (file.exists() && file.isFile() && file.canRead()) 
					return file;
			}
			
			return null;
		}
		
		private static class InnerClassLoader extends ClassLoader {
			private static final int BUFFER_SIZE = 1024;
			
			private InnerReloadableHandler<?> handler;
			private String className;
			private File classFile;
			private Class<?> clazz;
			private long lastModified;			
			
			private InnerClassLoader(InnerReloadableHandler<?> handler, String className, File classFile, long lastModified) {
				this.handler = handler;
				this.className = className;
				this.classFile = classFile;
				this.lastModified = lastModified;
			}

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
					return handler.loadClass(name, true);
				
				if (clazz != null)
					return clazz;
				
				synchronized (this) {
					if (!classFile.exists() || !classFile.isFile() || !classFile.canRead())
						throw new ClassNotFoundException();
					
					try (InputStream inputStream = new FileInputStream(classFile);
							BufferedInputStream bufferedInputStream = new BufferedInputStream(inputStream);
							ByteArrayOutputStream outputStream = new ByteArrayOutputStream();) {
						System.out.println("Loading class " + className + " from " + classFile);
						
						byte[] buffer = new byte[BUFFER_SIZE];
						int read = bufferedInputStream.read(buffer);
						
						while (read >= 0) {
							outputStream.write(buffer, 0, read);
							read = bufferedInputStream.read(buffer);
						}
						
						byte[] bytecode = outputStream.toByteArray();
						clazz = defineClass(className, bytecode, 0, bytecode.length);
						
						if (resolve)
							resolveClass(clazz);
						
						System.out.println("Loaded class " + className + " from " + classFile);
						return clazz;
					}
					catch (Throwable throwable) {
						throw new ClassNotFoundException(className, throwable.getCause());
					}
				}
			}
		}
		
	}

}
