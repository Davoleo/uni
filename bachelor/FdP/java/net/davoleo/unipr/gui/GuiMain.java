package net.davoleo.unipr.gui;

import javax.swing.*;

public class GuiMain {

    public static void main(String[] args)
    {
        JFrame firstFrame = new JFrame("Sample GUI");

        firstFrame.setSize(400, 400);
        firstFrame.setLocation(200, 100);
        firstFrame.add(new JLabel("Hello World!"), SwingConstants.CENTER);

        firstFrame.setVisible(true);
        firstFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        TestFrame1 test1 = new TestFrame1();
        test1.setVisible(true);
    }
}
