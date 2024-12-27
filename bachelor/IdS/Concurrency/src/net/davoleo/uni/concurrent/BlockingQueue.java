package net.davoleo.uni.concurrent;

public interface BlockingQueue<E> {

    E take() throws InterruptedException;

    void put (E element) throws InterruptedException;

    /**
     * @return  Integer.MAX_VALUE if not size-limited, otherwise the maximum achievable capacity
     */
    int remainingCapacity();

    boolean isEmpty();

    void clear();

}
