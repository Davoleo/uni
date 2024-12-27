package net.davoleo.uni.examples.ex09;

import java.util.List;

import net.davoleo.uni.examples.beans.Bean;
import net.davoleo.uni.examples.beans.BeanLoader;
import net.davoleo.uni.examples.ex09.models.simple.SimpleBook;
import net.davoleo.uni.examples.ex09.models.simple.SimpleStudent;

public class Example09 {
	private void go() {
		try {
			BeanLoader loader = new BeanLoader();

			List<SimpleStudent> studentBeans = loader.load(SimpleStudent.class, "Students.csv");

			for (Bean bean : studentBeans)
				System.out.println(bean);

			System.out.println();

			List<SimpleBook> bookBeans = loader.load(SimpleBook.class, "Books.csv");

			for (Bean bean : bookBeans)
				System.out.println(bean);
		} catch (Throwable throwable) {
			System.err.println("Cannot load beans with message " + throwable.getMessage());
		}
	}
	
	public static void main(String[] args) {
		new Example09().go();
	}
}
