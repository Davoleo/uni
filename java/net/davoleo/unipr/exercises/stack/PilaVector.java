package net.davoleo.unipr.exercises.stack;

import java.util.EmptyStackException;
import java.util.Vector;

@SuppressWarnings({"rawtypes", "unchecked"})
public class PilaVector implements Pila, Cloneable {

    private Vector vector;

    public PilaVector()
    {
        vector = new Vector();
    }

    public Object get(int i) {
        return vector.get(i);
    }

    @Override
    public void push(Object x)
    {
        vector.add(x);
    }

    @Override
    public Object pop()
    {
        if (isEmpty())
            throw new PilaVuota();
        return vector.remove(vector.size() - 1);
    }

    @Override
    public boolean isEmpty()
    {
        return vector.isEmpty();
    }

    @Override
    public int size()
    {
        return vector.size();
    }

    @Override
    public void clear()
    {
        vector.clear();
    }

    @Override
    protected Object clone() throws CloneNotSupportedException
    {
        super.clone();
        PilaVector stack = new PilaVector();
        stack.vector = (Vector) vector.clone();
        return stack;
    }

    @Override
    public String toString()
    {
        return vector.toString();
        //return '[' + String.join(",", ) + ']';
    }
}
