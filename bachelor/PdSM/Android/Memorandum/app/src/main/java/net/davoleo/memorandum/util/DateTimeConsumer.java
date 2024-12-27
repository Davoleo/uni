package net.davoleo.memorandum.util;

@FunctionalInterface
public interface DateTimeConsumer {

    void apply(int year, int month, int day, int hour, int minute);

}
