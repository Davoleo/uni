package net.davoleo.unipr.exercises.equationgui;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;

public class Equ2 extends JFrame {

    private static final int VALID_INPUTS = 0;
    private static final int EMPTY_INPUTS = -1;
    private static final int INVALID_INPUTS = -2;

    private final JTextField firstCoeffBox;
    private final JTextField secondCoeffBox;
    private final JTextField thirdCoeffBox;

    private final JLabel outputLabel;
    private final JLabel outputLabel2;

    public Equ2()
    {
        super("Risolutore equazioni");

        this.setSize(500, 320);
        this.setLayout(new BorderLayout());

        JPanel mainPanel = new JPanel();
        mainPanel.setBorder(new TitledBorder("Risoluzione equazione di 2o grado ax^2 + bx + c = 0"));
        mainPanel.setLayout(new BorderLayout());

        // BEGIN: --- Controls on the left ---
        JPanel ioPanel = new JPanel();
        ioPanel.setLayout(new GridLayout(8, 1, 5, 5));

        ioPanel.add(new JLabel("Primo coefficiente (a)"));
        firstCoeffBox = new JTextField();
        ioPanel.add(firstCoeffBox);

        ioPanel.add(new JLabel("Secondo coefficiente (b)"));
        secondCoeffBox = new JTextField();
        ioPanel.add(secondCoeffBox);

        ioPanel.add(new JLabel("Terzo coefficiente (c)"));
        thirdCoeffBox = new JTextField();
        ioPanel.add(thirdCoeffBox);

        outputLabel = new JLabel();
        ioPanel.add(outputLabel);

        outputLabel2 = new JLabel();
        ioPanel.add(outputLabel2);

        mainPanel.add(ioPanel, BorderLayout.WEST);
        // END: --- Controls on the left ---

        // BEGIN: --- Buttons on the right ---
        JPanel buttonsPanel = new JPanel();
        buttonsPanel.setLayout(new BorderLayout());

        JPanel buttonsSubContainer = new JPanel();
        Equ2Listener listener = new Equ2Listener(this);
        buttonsSubContainer.setLayout(new GridLayout(2, 1, 0, 10));

        JButton computeButton = new JButton("Calcola");
        computeButton.addActionListener(listener);
        buttonsSubContainer.add(computeButton);

        JButton cleanButton = new JButton("Pulisci");
        cleanButton.addActionListener(listener);
        buttonsSubContainer.add(cleanButton);

        buttonsPanel.add(buttonsSubContainer, BorderLayout.NORTH);
        mainPanel.add(buttonsPanel, BorderLayout.EAST);
        // END: --- Buttons on the right ---

        //BEGIN: --- Exit Panel
        JPanel exitPanel = new JPanel();
        exitPanel.setLayout(new FlowLayout());

        JButton exitButton = new JButton("Esci");
        exitButton.addActionListener(listener);
        exitPanel.add(exitButton);
        //END: --- Exit Panel

        this.add(mainPanel, BorderLayout.NORTH);
        this.add(exitPanel, BorderLayout.SOUTH);
    }


    int validateInputs(double[] coeffs)
    {
        String coeffString1 = firstCoeffBox.getText();
        String coeffString2 = secondCoeffBox.getText();
        String coeffString3 = thirdCoeffBox.getText();

        if (coeffString1.isEmpty() || coeffString2.isEmpty() || coeffString3.isEmpty())
            return EMPTY_INPUTS;

        try {
            double coeff1 = Double.parseDouble(coeffString1);
            double coeff2 = Double.parseDouble(coeffString2);
            double coeff3 = Double.parseDouble(coeffString3);
            coeffs[0] = coeff1;
            coeffs[1] = coeff2;
            coeffs[2] = coeff3;
        }
        catch (NumberFormatException e) {
            return INVALID_INPUTS;
        }

        return VALID_INPUTS;
    }

    void computeResults() {
        double[] coeffs = new double[3];

        int status = validateInputs(coeffs);

        if (status == EMPTY_INPUTS)
            outputLabel.setText("Immettere prima tutti i coefficienti");
        else if (status == INVALID_INPUTS)
            outputLabel.setText("Errore nei numeri inseriti");
        else {
            double delta = (coeffs[1] * coeffs[1]) - (4 * coeffs[0] * coeffs[2]);

            if (delta < 0) {
                outputLabel.setText("Discriminante Negativo");
                return;
            }

            double sol1 = (-coeffs[1] + Math.sqrt(delta)) / (2 * coeffs[0]);
            double sol2 = (-coeffs[1] - Math.sqrt(delta)) / (2 * coeffs[0]);
            outputLabel.setText("Soluzione 1 (x_1) = " + sol1);
            outputLabel2.setText("Soluzione 2 (x_2) = " + sol2);
        }
    }

    void resetIOControls() {
        firstCoeffBox.setText("");
        secondCoeffBox.setText("");
        thirdCoeffBox.setText("");
        outputLabel.setText("");
        outputLabel2.setText("");
    }

    void exit() {
        System.exit(0);
    }
}
