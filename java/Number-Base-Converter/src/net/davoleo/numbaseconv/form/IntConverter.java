package net.davoleo.numbaseconv.form;

import javax.swing.*;
import java.awt.*;

public class IntConverter {
    private JPanel panel1;
    private JSpinner base1;

    private Container container;

    public IntConverter() {
        container = getPanel1();
    }

    public JPanel getPanel1() {
        return panel1;
    }
}
