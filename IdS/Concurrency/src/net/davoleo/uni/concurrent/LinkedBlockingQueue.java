package net.davoleo.uni.concurrent;

import java.util.LinkedList;

public class LinkedBlockingQueue<E> implements BlockingQueue<E> {

    private final LinkedList<E> queue;

    public LinkedBlockingQueue()
    {
        queue = new LinkedList<>();
    }

    @Override
    public E take() throws InterruptedException
    {
        synchronized (queue) {
            while (queue.size() == 0)
                queue.wait();

            E elem = queue.removeFirst();

            //If after removing there are still other elements we notify another consumer
            if (queue.size() > 0)
                queue.notify();

            return elem;
        }
    }

    @Override
    public void put(E element) throws InterruptedException
    {
        synchronized (queue) {
            queue.addLast(element);

            //New element added -> notify other consumers
            if (queue.size() == 1)
                queue.notify();
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
        return queue.isEmpty();
    }

    @Override
    public void clear()
    {
        synchronized (queue) {
            queue.clear();
        }
    }
}
