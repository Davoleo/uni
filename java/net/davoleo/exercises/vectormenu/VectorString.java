package net.davoleo.exercises.vectormenu;

public class VectorString {

    private final String[] array = new String[100];
    private int size = 0;

    public boolean add(String elem)
    {
        if (size < array.length) {
            array[size++] = elem;
            return true;
        }
        else return false;
    }

    public String getFirstShortest() {
        String shortest = array[0];

        for (int i = 1; i < size; i++)
        {
            if (shortest.length() > array[i].length())
                shortest = array[i];
        }

        return shortest;
    }

    public String getFirstStartingWith(char chara)
    {
        for (String string : array)
        {
            if (string.charAt(0) == chara)
                return string;
        }

        return "";
    }

    public void sort()
    {
        for (int i = 0; i < size; i++) {
            int min = i;
            for (int j = min; j < size; j++)
            {
                if (array[min].compareTo(array[j]) > 0)
                    min = j;
            }

            if (min != i) {
                String old = array[i];
                array[i] = array[min];
                array[min] = old;
            }
        }
    }

    public void print()
    {
        System.out.println("[");

        for (int i = 0; i < size; i++)
            System.out.println('\t' + array[i]);

        System.out.println("]");
    }

    public boolean isEmpty()
    {
        return size == 0;
    }
}
