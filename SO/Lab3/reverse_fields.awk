{
    for (i=NF; i>=1; i--)
        printf "%s", $i;
    printf "\n";
}

# Regex condition
/t.+e/ {
    print NR, "<- Questa linea contiene una t seguita da almeno 1 carattere e poi una e" 
}