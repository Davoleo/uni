%% Scheda 1
% Es 3

% Punto 1
% Calcolare il raggio di una sfera che ha un volume del 30% piu grande di una sfera
% di raggio 5 cm.
r1 = 5;
v1 = 4/3 * pi * r1^3;
v2 = 1.3 * v1;
r2 = (v2 * (3/4) / pi)^(1/3)

% Punto 2
% Errore assoluto e relativo su approssimazioni polinomiali di e^x
x = 0.1;
pol1 = 1 + x;
pol2 = 1 + x + (x^2 / 2);

% errori assoluti
ea1 = abs(exp(x) - pol1)
ea2 = abs(exp(x) - pol2)

% errori relativi
er1 = (abs(exp(x) - pol1)) / exp(x)
er2 = (abs(exp(x) - pol2)) / exp(x)

% Punto 3 
% Radici dell'equazioni
roots1 = roots([2, -4, -1])
roots2 = roots([1, 0, 2, 0, -3])
%Dopo aver sostituito t = x^2?
roots2b = roots([1, 2, -3])
roots2c1 = (-2-sqrt(2.^2 - 4*1*-3)) / (2 * 1)

%% -- Comandi Array
% Norme di vettori
x = [1 -2]
norm1 = sum(abs(x))
norm1alt = norm(x, 1)

norm2 = sqrt(sum(x.^2))
norm2alt = norm(x, 2)

norminf = max(abs(x))
norminfalt = norm(x, inf)

% Norme indotte su matrici
A = [1 2 3; 7 8 0; 1 1 1];
% Vettore riga di somme di tutti i valori in colonna
sum(A)
% Fa il sort dei valori in colonna posizionandoli in ordine crescente
sort(A)



%% Scheda 1 Parte 2
% Es 4
x = [1:10]
y = [10:-1:1]'
prod = x * y

z = sin(linspace(0, 1, 11))'

% Es 5
x = [25:3:91]
y = [100:-2:10]
z = linspace(-15, -10, 33)
