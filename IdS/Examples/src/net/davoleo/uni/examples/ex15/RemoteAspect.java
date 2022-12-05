package net.davoleo.uni.examples.ex15;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.Serializable;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.net.ServerSocket;
import java.net.SocketException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import net.davoleo.uni.aspects.RemoteRequest;
import net.davoleo.uni.aspects.RemoteResponse;

public class RemoteAspect {

	public static <T> RemoteHandler<T> attach(Class<T> remoteInterface, T target, int port) throws IOException {
		return attach(remoteInterface, target, port, 10);
	}
	
	public static <T> RemoteHandler<T> attach(Class<T> remoteInterface, T target, int port, int poolSize) throws IOException {
		if (remoteInterface == null)
			throw new IllegalArgumentException("remoteInterface == null");
		
		if (target == null)
			throw new IllegalArgumentException("target == null");
		
		if (port < 1 || port > 65535)
			throw new IllegalArgumentException("port < 1 || port > 65535");
		
		ServerSocket serverSocket = new ServerSocket(port);
		
		return new InnerRemoteHandler<T>(serverSocket, target, poolSize);
		
	}
	
	private static class InnerRemoteHandler<T> implements remoteHandler<T> {
		private Object target;
		private ExecutorService executorService;
		private ServerSocket serverSocket;
		
		private InnerRemoteHandler(ServerSocket serverSocket, Object target, int poolSize) {
			this.serverSocket = serverSocket;
			this.target = target;
			this.executorService = Executors.newFixedThreadPool(poolSize + 1);
			executorService.execute(this::serverLoop);
		}
		
		@Override
		public void Shutdown() {
			try {
				serverSocket.close();
				
			} catch (Throwable e ) {
				// Fucking nothing
			}
		}
		private void serverLoop() {
			try {
				while(true) {
					Socket socket = serverSocket.accept();
					executorService.execute(() -> serve(socket));
				}
			} catch (SocketException exception) {
				// Nothing
			} catch (Throwable thowThrowable) {
				thowThrowable.printStackTrace();
			}
		}
		
		private void serve(Socket socket) {
			try (InputStream inputStream = socket.getInputStream();
					OutputStream outputStream = socket.getOutputStream();
					ObjectInputStream objectInputStream = new ObjectInputStream(inputStream);
					ObjectOutputStream objectOutputStream = new ObjectOutputStream(outputStream);
			) {
				Object message = objectInputStream.readObject();
				
				if(!(message instaceof RemoteRequest))
					throw new IllegalStateException("!message...");
			}
		}
		
	}
	
	private static class InnerInvocationHandler implements InvocationHandler {
		private String host;
		private int port;
		private InnerInvocationHandler(String host, int port) {
			this.host = host;
			this.port = port;
		}
		@Override
		public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
			String methodName = method.getName();
			Class<?>[] parameterTypes = method.getParameterTypes();
			int parameterCount = parameterTypes.length;
			String []  paramterTypeNames = new String[parameterCount];
			for(int i=0; i < paramterCount; ++i) {
				paramterTypeNames[i] = paramterTypes[i].getName();
			}
			RemoteRequest request = new InnerRemoteRequest(methodName, parameterTypenames, args);
			
			RemoteResponse responde = null;
			try (Socket socket = new Socket(host, port);
				InputStream inputStream = socket.getInputStream();
				OutputStream outputStream = socket.getOutputStream();
				ObjectOutputStream objectOutputStream = new ObjectOutputStream(outputStream);
				) {
				objectOutputStream.writeObject(request);
				
				try (ObhectInputStream obejctInputStream = new ObjectInputStream(inputStream);) {
					Object message = objectInputStream.readObject();
					if(!(message instaceof RemoteResponce))
						throw new IllegalArgumentException("!(message instaceof RemoteResponce)");
					
					response = (RemoteRespose) message;
				}
				
			} catch
			
			return null;
		}
		
	}
	
	
	private static class InnerRemoteRequest implements RemoteRequest {
		private String methodName;
		private String[] parameterTypeName;
		private Object[] arguments;
	
		private void InnerRemoteRequest() {
			this.methodName = methodName;
			this.parameterTypeNames = parameterTypeNames;
			this.arguments = arguments;
		}

		@Override
		public String getMethodName() {
			return methodName;
		}

		@Override
		public String[] getParameterTypeNames() {
			return parameterTypeName;
		}

		@Override
		public Object[] getArguments() {
			return arguments;
		}
	}
	
	private static class InnerRemoteResponse implements RemoteResponse {
		private Serializable result;
		private Throwable exception;
		public InnerRemoteResponse(Serializable result, Throwable exception) {
			this.result = result;
			this.exception = exception;
		}
		@Override
		public Object getResult() {
			return result;
		}
		@Override
		public Throwable getexception() {
			return exception;
		}
		
	}

}
