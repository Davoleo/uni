package net.davoleo.uni.examples.ex13;

import java.util.ArrayList;
import java.util.List;

import net.davoleo.uni.aspects.PersistentAspect;
import net.davoleo.uni.aspects.PersistentHandler;
import net.davoleo.uni.examples.ex09.models.Book;
import net.davoleo.uni.examples.ex09.models.simple.SimpleBook;

public class Example13 {
	
	private void printAndAddBooks(List<Book> books) {
		
		int s = books.size();
		
		if(s > 0) {
			System.out.println("Current books:");
			
			for(Book book : books)
				System.out.println(book);			
		}
		
		for (int i = 1; i <= 3; ++i) {
			int n = 10 + (int)(90 * Math.random());
			books.add(new SimpleBook(s + i, "Author #" + n, "Title #" + n));
		}
	}

	private void go() {
		try {
			PersistentHandler<ArrayList<Book>> bookHandler = PersistentAspect.attach("Books.dat", new ArrayList<>());
			List<Book> books = bookHandler.get();
			
			printAndAddBooks(books);
			
			bookHandler.commit();
			
			System.out.println("Books Saved");
		} catch (Throwable throwable) {
			throwable.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		new Example13().go();
	}
	
}
