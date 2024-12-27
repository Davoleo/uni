package net.davoleo.uni.examples.ex12;

import net.davoleo.uni.aspects.LoggingAspect;

import java.util.Comparator;
import java.util.Set;
import java.util.TreeSet;

public class Example12 {
	
	private void go() {
		Comparator<String> comparator = new CaseInsensitiveComparator();
		comparator = LoggingAspect.attach(comparator);
		
		Set<String> set = new TreeSet<>(comparator);

		set.add("Verdi");
		set.add("Bianchi");
		set.add("Neri");
		set.add("Rossi");
		
		set.contains("Neri");
		set.contains("Viola");
	}
	
	public static void main(String[] args) {
		new Example12().go();
	}
	
	private static class CaseInsensitiveComparator implements Comparator<String> {
		@Override
		public int compare(String o1, String o2) {
			if (o1 == null || o2 == null) 
				throw new IllegalArgumentException("o1 == null || o2 == null");
			return o1.compareToIgnoreCase(o2);
		}
	}

}
