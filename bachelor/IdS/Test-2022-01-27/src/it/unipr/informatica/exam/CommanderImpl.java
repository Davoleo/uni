package it.unipr.informatica.exam;

public class CommanderImpl implements Commander {

	@Override
	public boolean command(Slave slave) {
		
		new Thread(() -> {
			slave.executePartB();
			synchronized (this) {
				this.notify();
			}
			slave.executePartC();
		}).start();
		
		slave.executePartA();
		synchronized (this) {
			try {
				this.wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		return slave.finish() == 0;
	}

}
