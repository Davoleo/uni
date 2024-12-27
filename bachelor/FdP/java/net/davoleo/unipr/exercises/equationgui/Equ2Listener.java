package net.davoleo.unipr.exercises.equationgui;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Equ2Listener implements ActionListener {

    private Equ2 window;

    public Equ2Listener(Equ2 window)
    {
        this.window = window;
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        String buttonText = ((JButton) e.getSource()).getText();

        switch (buttonText) {
            case "Calcola":
                window.computeResults();
                break;
            case "Pulisci":
                window.resetIOControls();
                break;
            case "Esci":
                window.exit();
                break;
            default:
               JOptionPane.showMessageDialog(window, "Questo comando non è ancora stato implementato!", "Errore", JOptionPane.ERROR_MESSAGE);
        }
    }
}
