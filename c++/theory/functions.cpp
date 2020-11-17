//num1, num2 e num3 sono parametri della funzione
//l'int prima dell'identificatore della funzione è il tipo del  risultato
int max(int num1, int num2, int num3) {
    //Variabile locale nella funzione
    int temp;

    if (num1 > num2)
        temp = num1;
    else
        temp = num2;

    if (temp > num3)
        return temp;
    else
        return num3;
}

int main() {

    //Chiamata di funzione
    max(4, 6, 2);

    return 0;
}