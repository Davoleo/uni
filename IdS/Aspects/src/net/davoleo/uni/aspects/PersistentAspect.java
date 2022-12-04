package net.davoleo.uni.aspects;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.Serializable;

public class PersistentAspect {
	
	public static <T extends Serializable> PersistentHandler<T> attach(String filename, T object) throws IOException {
		return attach(new File(filename), object);
	}
	
	public static <T extends Serializable> PersistentHandler<T> attach(File file, T object) throws IOException {
		if (object == null)
			throw new IllegalArgumentException("object == null");
		
		if (file == null)
			throw new IllegalArgumentException("file == null");
		
		if (file.exists() && !file.isFile())
			throw new IllegalArgumentException("File doesn't exist or is not an actual file.");
		
		InnerPersistentHandler<T> handler = new InnerPersistentHandler<>(file);
		
		if (file.exists())
			handler.load();
		else
			handler.target = object;
		
		return handler;
	}
	
	private PersistentAspect() {}
	
	private static class InnerPersistentHandler<T extends Serializable> implements PersistentHandler<T> {
		private T target;
		private File file;
		
		private InnerPersistentHandler(File file) {
			this.file = file;
			this.target = null;
		}

		@Override
		public T get() {
			if (target == null)
				throw new IllegalStateException("target == null");
			return target;
		}

		@Override
		public void rollback() throws IOException {
			load();
		}

		@Override
		public void commit() throws IOException {
			save();
		}
		
		private void load() throws IOException {
			
			try (InputStream inputStream = new FileInputStream(file);
					BufferedInputStream bufferedInputStream = new BufferedInputStream(inputStream);
					ObjectInputStream objectInputStream = new ObjectInputStream(bufferedInputStream)) {
				Object object = objectInputStream.readObject();
				
				@SuppressWarnings("unchecked")
				T result = (T) object;
				
				target = result;
			}
			catch (IOException e) {
				throw e;
			}
			catch (Throwable throwable) {
				throw new IOException(throwable);
			}
		}
		
		private void save() throws IOException {
			if (target == null)
				throw new IllegalArgumentException("target == null");
			
			try (OutputStream outputStream = new FileOutputStream(file);
					BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(outputStream);
					ObjectOutputStream objectOutputStream = new ObjectOutputStream(bufferedOutputStream)) {
				objectOutputStream.writeObject(target);
			} 
			catch (IOException e) {
				throw e;
			}
			catch (Throwable throwable) {
				throw new IOException(throwable);
			}
			
		}
		
		
		
	}
	
}
