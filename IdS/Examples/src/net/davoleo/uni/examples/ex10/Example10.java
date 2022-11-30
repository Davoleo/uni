package net.davoleo.uni.examples.ex10;

import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

import net.davoleo.uni.examples.ex09.models.Student;

public class Example10 {
	
	private Object handler(Object proxy, Method method, Object[] arguments) throws Throwable {
		String methodName= method.getName();
		
		switch (methodName) {
		case "getID":
			return 1;
		case "getSurname":
			return "Verdi";
		case "getName":
			return "Giuseppe";
		default:
			throw new IllegalArgumentException("Unsupported Method: " + methodName);
		}
	}
	
	private void go() {
		//Method invocation overridden via proxy instance  
		Student student = (Student) Proxy.newProxyInstance(getClass().getClassLoader(), new Class<?>[] {Student.class}, this::handler);
		
		System.out.println("ID: " + student.getID());
		System.out.println("Name: " + student.getName());
		System.out.println("Surname: " + student.getSurname());
		
		//if we call toString the overridden method in SimpleStudent will not be called since we don't have an object and
		//The proxy tries to do its work but defaults to throwing an illegalArgumentException
		System.out.println(student.toString());
	}
	
	public static void main(String[] args) {
		new Example10().go();
	}
}
