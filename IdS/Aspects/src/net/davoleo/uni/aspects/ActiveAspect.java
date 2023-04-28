package net.davoleo.uni.aspects;

import net.davoleo.uni.concurrent.Callback;
import net.davoleo.uni.concurrent.ExecutorService;
import net.davoleo.uni.concurrent.Executors;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.Arrays;

public class ActiveAspect {
	
	public static <T, A extends Active<T>> ActiveHandler<A> attach(Class<A> activeInterface, T target) {
		return attach(activeInterface, target, 10);
	}
	
	public static <T, A extends Active<T>> ActiveHandler<A> attach(Class<A> activeInterface, T target, int poolSize) {
		if (activeInterface == null)
			throw new IllegalArgumentException("activeInterface == null");
		
		if (target == null)
			throw new IllegalArgumentException("target == null");
		
		if (poolSize < 1)
			throw new IllegalArgumentException("poolSize < 1");
		
		InnerInvocationHandler invocationHandler = new InnerInvocationHandler(target, poolSize);
		
		Object proxy = Proxy.newProxyInstance(target.getClass().getClassLoader(), new Class<?>[] { activeInterface }, invocationHandler);
		
		@SuppressWarnings("unchecked")
		A object = (A) proxy;
		
		return new InnerActiveHandler<A>(object, invocationHandler);
	}
	
	private static class InnerActiveHandler<A extends Active<?>> implements ActiveHandler<A> {

		private A proxy;
		private InnerInvocationHandler handler;
		
		public InnerActiveHandler(A proxy, InnerInvocationHandler handler) {
			this.proxy = proxy;
			this.handler = handler;
		}
		
		@Override
		public A get() {
			return proxy;
		}

		@Override
		public void shutdown() {
			handler.shutdown();
		}
		
	}
	
	private static class InnerInvocationHandler implements InvocationHandler {

		private ExecutorService executorService;
		private Object target;
		
		private InnerInvocationHandler(Object target, int poolSize) {
			this.target = target;
			this.executorService = Executors.newFixedThreadPool(poolSize);
		}
		
		private void shutdown() {
			executorService.shutdown();
		}
		
		@Override
		public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
			Class<?>[] parameterTypes = method.getParameterTypes();
			int parameterCount = parameterTypes.length;
			
			Class<?> targetClass = target.getClass();
			
			if (parameterCount > 0 && parameterTypes[parameterCount - 1] == Callback.class) {
				parameterCount--;
				
				Class<?>[] newParameterTypes = Arrays.copyOf(parameterTypes, parameterCount);
				Method targetMethod = targetClass.getMethod(method.getName(), newParameterTypes);

				@SuppressWarnings("unchecked")
				Callback<Object> callback = (Callback<Object>) args[parameterCount];
				
				Object[] newArguments = Arrays.copyOf(args, parameterCount);
				
				executorService.submit(() -> invokeMethod(targetMethod, newArguments), callback);
				
				return null;
			}
			else {
				Method targetMethod = targetClass.getMethod(method.getName(), parameterTypes);
				return executorService.submit(() -> invokeMethod(targetMethod, args));
			}
		}
		
		private Object invokeMethod(Method targetMethod, Object[] arguments) throws Exception {
			try {
				return targetMethod.invoke(target, arguments);
			} catch (InvocationTargetException e) {
				Throwable cause = e.getCause();
				
				if (cause instanceof RuntimeException) 
					throw (RuntimeException) cause;
				
				if (cause instanceof Exception)
					throw (Exception) cause;
				
				throw e;
			}
		}
		
	}

}
