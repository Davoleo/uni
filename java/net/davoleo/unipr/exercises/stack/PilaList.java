package net.davoleo.unipr.exercises.stack;

import java.util.EmptyStackException;

public class PilaList implements Pila, Cloneable {

    private static class Elem {
        private Object info;
        private Elem next;
    }

    Elem linkedList;
    int size;

    public PilaList()
    {
        linkedList = null;
        size = 0;
    }

    @Override
    public void push(Object x)
    {
        if (isEmpty()) {
            linkedList = new Elem();
            linkedList.info = x;
            linkedList.next = null;
        }
        else {
            Elem newElem = new Elem();
            newElem.next = linkedList;
            newElem.info = x;
            linkedList = newElem;
        }

        size++;
    }

    @Override
    public Object pop()
    {
        if (isEmpty())
            throw new PilaVuota();

        Object toReturn = linkedList.info;
        linkedList = linkedList.next;

        size--;
        return toReturn;
    }

    @Override
    public boolean isEmpty()
    {
        return linkedList == null;
    }

    @Override
    public int size()
    {
        return size;
    }

    @Override
    public void clear()
    {
        linkedList = null;
        size = 0;
    }

    @Override
    protected Object clone() throws CloneNotSupportedException
    {
        super.clone();
        PilaList newList = new PilaList();
        Object[] elems = new Object[size];

        Elem list = linkedList;
        for (int i = elems.length - 1; i >= 0; i--)
        {
            elems[i] = list.info;
            list = list.next;
        }

        for (Object elem : elems)
            newList.push(elem);

        return newList;
    }

    @Override
    public String toString()
    {
        Elem list = linkedList;
        String[] array = new String[size];
        for (int i = 0; i < size; i++) {
            array[i] = list.info.toString();
            list = list.next;
        }

        return '[' + String.join(",", array) + ']';
    }
}
