package net.davoleo.uni.examples.ex09.models.simple;

import net.davoleo.uni.examples.ex09.models.Student;

public class SimpleStudent implements Student, Cloneable {
	
	private static final long serialVersionUID = 1357573549375503999L;
	
	private int id;
	private String name;
	private String surname;
	
	public SimpleStudent() {
		this.id = 0;
		this.name = this.surname = "";
	}
	
	public SimpleStudent(int id, String name, String surname) {
		if (id < 1)
			throw new IllegalArgumentException("id < 1");

		if (name == null || name.length() == 0)
			throw new IllegalArgumentException("author == null || author.length() == 0");

		if (surname == null || surname.length() == 0)
			throw new IllegalArgumentException("title == null || title.length() == 0");

		this.id = id;
		this.name = name;
		this.surname = surname;
	}
	
	@Override
	public int getID() {
		return id;
	}
	
	public void setID(int id) {
		if (id < 1)
			throw new IllegalArgumentException("id < 1");

		this.id = id;
	}

	@Override
	public String getName() {
		return name;
	}
	
	public void setName(String author) {
		if (author == null || author.length() == 0)
			throw new IllegalArgumentException("author == null || author.length() == 0");

		this.name = author;
	}

	@Override
	public String getSurname() {
		return surname;
	}
	
	public void setSurname(String title) {
		if (title == null || title.length() == 0)
			throw new IllegalArgumentException("title == null || title.length() == 0");

		this.surname = title;
	}
	
	@Override
	public boolean equals(Object obj) {
		if (!(obj instanceof SimpleStudent))
			return false;
		
		
		SimpleStudent other = (SimpleStudent) obj;
		return id == other.id && surname.equals(other.id) && name.equals(other.id);
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return new SimpleStudent(id, name, surname);
	}
	
	@Override
	public int hashCode() {
		return id + surname.hashCode() + name.hashCode();
	}
	
	@Override
	public String toString() {
		return "ID=" + id + ", author=" + name + ", title=" + surname;
	}

}
