package net.davoleo.unipr.gui;

import javax.swing.*;

public class TestFrame1 extends JFrame {

    public TestFrame1()
    {
        super("Test 1");

        this.setSize(400, 400);
        this.setLocation(600, 100);

        JPanel panel = new JPanel();
        panel.setLayout(null); // null -> Absolute positioning
        this.add(panel);

        JButton btn = new JButton("Press Me!");
        btn.setBounds(150, 50, 100, 20);
        panel.add(btn);

        btn.addActionListener(event -> System.out.println("Pressed a button"));

        JLabel label = new JLabel("Helllo WArudo");
        label.setBounds(100, 100, 100, 30);
        panel.add(label);

        JTextField textField = new JTextField();
        textField.setBounds(200, 100, 100, 40);
        panel.add(textField);

    }
}
