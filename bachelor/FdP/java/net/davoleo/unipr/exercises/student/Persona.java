package net.davoleo.unipr.exercises.student;

import java.io.PrintStream;

public class Persona {

    protected String name;
    protected String surname;
    protected String address;

    public Persona() {
        name = "xxx";
        surname = "xxx";
        address = "xxx";
    }

    public Persona(String name, String surname)
    {
        if (Character.isLowerCase(name.charAt(0)))
            this.name = Character.toUpperCase(name.charAt(0)) + name.substring(1);
        if (Character.isLowerCase(surname.charAt(0)))
            this.surname = Character.toUpperCase(surname.charAt(0)) + surname.substring(1);

        address = "xxx";
    }

    public void setAddress(String address)
    {
        this.address = address;
    }

    public String getAddress()
    {
        return address;
    }

    void stampa(PrintStream stream) {
        stream.println(name + ' ' + surname);
        stream.println(address);
    }
}
