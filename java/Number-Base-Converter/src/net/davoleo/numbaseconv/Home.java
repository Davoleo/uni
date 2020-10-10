package net.davoleo.numbaseconv;

import net.davoleo.numbaseconv.form.IntConverter;

import javax.swing.*;
import java.awt.*;

public class Home {

    public static JFrame mainWindow;

    public static Container mainContent;
    public static Container intConverter;

    public static void main(String[] args) {
        mainWindow = new JFrame("Number Base Converter");
        intConverter = new IntConverter().getPanel1();

        mainWindow.setResizable(false);

        mainContent = mainWindow.getContentPane();
        mainContent.setPreferredSize(new Dimension(300, 100));

        FlowLayout layout = new FlowLayout(FlowLayout.CENTER, 5, 5);
        mainContent.setLayout(layout);

        JLabel welcomeLabel = new JLabel("Welcome to my portable Base Converter");
        welcomeLabel.setOpaque(true);

        JButton intConvButton = new JButton("Int Converter");
        intConvButton.addActionListener(actionEvent -> {
            mainWindow.setContentPane(intConverter);
            mainWindow.revalidate();
            mainWindow.repaint();
        });

        mainContent.add(welcomeLabel);
        mainContent.add(intConvButton);

        mainWindow.pack();
        mainWindow.setVisible(true);
        mainWindow.setLocation(centerScreen(mainWindow.getWidth(), mainWindow.getHeight()));
        mainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    }

    private static Point centerScreen(int formWidth, int formHeight) {
        return new Point(
                (Toolkit.getDefaultToolkit().getScreenSize().width / 2) - (formWidth / 2),
                (Toolkit.getDefaultToolkit().getScreenSize().height / 2) - (formHeight / 2)
        );
    }
}
