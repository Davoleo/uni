% Ex. 6 - Scheda Interpolazione

x = [0.49 0.64 0.81];
y = [0.7 0.8 0.9];
coeff = polyfit(x,y,2);
coeff2 = polyfit([0.49 0.64 0.81 0.36], [0.7 0.8 0.9 0.6], 3);

y = polyval(coeff, 0.6);
y2 = polyval(coeff2, 0.6);

err = abs(y - sqrt(0.6))
err2 = abs(y2 - sqrt(0.6))