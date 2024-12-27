package net.davoleo.unipr;

public class NullDenominatorException extends ArithmeticException {

    public NullDenominatorException()
    { }

    public NullDenominatorException(String s)
    {
        super(s);
    }
}
