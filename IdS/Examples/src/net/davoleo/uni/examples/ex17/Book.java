package net.davoleo.uni.examples.ex17;

import net.davoleo.uni.examples.beans.Bean;

public interface Book extends Bean, Cloneable {
	
	int getID();

	String getAuthor();

	String getTitle();
	
	Book clone();

}
