package it.unipr.informatica.exam;

public class Message {
	
	private final int value;
	
	public Message(int value) {
		this.value = value;
	}
	
	public int getValue() {
		return value;
	}
	
	public Message decremented() {
		return new Message(value-1);
	}
}
