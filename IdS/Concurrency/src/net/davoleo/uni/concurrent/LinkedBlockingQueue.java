package net.davoleo.uni.concurrent;

public class LinkedBlockingQueue<E> implements BlockingQueue<E> {

    private Node head;
    private Node tail;
    
    private final Object mutex;

    public LinkedBlockingQueue()
    {
        head = null;
        tail = null;
        mutex = new Object();
    }

    @Override
    public E take() throws InterruptedException
    {
        synchronized (mutex) {
            while (isEmpty())
                mutex.wait();

            @SuppressWarnings("unchecked")
			E elem = (E) head.value;
            head = head.next;

            if (head == null)
            	tail = null;
            else //after removing there are still other elements we notify another consumer
                mutex.notify();

            return elem;
        }
    }

    @Override
    public void put(E element) throws InterruptedException
    {
        synchronized (mutex) {
    		Node node = new Node();
    		node.next = null;
    		node.value = element;
        	
        	if (isEmpty()) {
        		head = tail = node;
			}
        	else {
        		tail.next = node;
        		tail = node;
        	}
        	
        	//Only 1 element in the list -> notify waiting consumer
        	if (head.next == null) {
        		mutex.notify();
			}
        }
    }

    @Override
    public int remainingCapacity()
    {
        return Integer.MAX_VALUE;
    }

    @Override
    public boolean isEmpty()
    {
        synchronized (mutex) {
			return head == null;
		}
    }

    @Override
    public void clear()
    {
        synchronized (mutex) {
            head = tail = null;
        }
    }
    
    private static class Node {
    	private Object value;
    	private Node next;
    }
}
