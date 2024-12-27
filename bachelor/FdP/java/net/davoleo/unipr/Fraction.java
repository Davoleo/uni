package net.davoleo.unipr;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.Scanner;

public class Fraction {

    private int num;
    private int den;

    public Fraction()
    {
        num = 0;
        den = 1;
    }

    public Fraction(int num)
    {
        this.num = num;
        this.den = 1;
    }

    public Fraction(int num, int den)
    {
        this.num = num;
        if (den != 0)
            this.den = den;
        else
            throw new NullDenominatorException("Fraction was initialized with null denominator!");
    }

    public void print(PrintStream stream)
    {
        stream.println(this);
    }

    public void read(InputStream source)
    {
        int num, den;
        Scanner scanner = new Scanner(source);
        String fracString = scanner.nextLine();
        int sepIndex = fracString.indexOf('/');
        num = Integer.parseInt(fracString.substring(0, sepIndex));
        den = Integer.parseInt(fracString.substring(sepIndex + 1));
        new Fraction(num, den);
    }

    Fraction sum(final Fraction other)
    {
        Fraction result = new Fraction();
        result.den = other.den * this.den;
        result.num = other.num * this.den + this.num * other.den;
        return result;
    }

    //Getters and setters
    public Fraction withNumerator(int num)
    {
        this.num = num;
        return this;
    }

    public Fraction withDenominator(int den)
    {
        if (den != 0)
            this.den = den;
        else
            throw new ArithmeticException("Denominator can't be 0");
        return this;
    }

    public int num()
    {
        return num;
    }

    public int den()
    {
        return den;
    }

    public double compute() {
        return (double) num / den;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Fraction) {
            Fraction frac = ((Fraction) obj);
            return this.num == frac.num && this.den == frac.den;
        }
        else if (obj instanceof Integer) {
            if (this.num % this.den == 0) {
                int div = num / den;
                return div == 0;
            }
            return false;
        }
        return false;
    }

    @Override
    public String toString()
    {
        return String.valueOf(num) + '/' + den;
    }
}
