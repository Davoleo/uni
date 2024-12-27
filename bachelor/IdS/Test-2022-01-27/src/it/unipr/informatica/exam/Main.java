package it.unipr.informatica.exam;

import java.util.ArrayList;
import java.util.List;

public class Main {
	
	public static final int S = 10;
	
	public static void main(String[] args) {
		SlaveManager slaveManager = SlaveManager.get();
		Commander commander = new CommanderImpl();
		
		List<Slave> list = new ArrayList<>(S);
		for (int i = 0; i < S; i++) {
			list.add(slaveManager.newDummySlave());
		}
		
		list.forEach(slave -> commander.command(slave));
	}

}
