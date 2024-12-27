; direttive per specificare il modello del processore
.8086
.model small

.data ;definisce segmenti di dati
a db 09h ; db = define byte (variabile di tipo byte (8 bit)) con il numero 09
a dw 1A02h ; dw = define word (variabile di tipo word (16bit)) con il numero 1A02h

.code ; pseudoistruzione / direttiva | inizio del segmento di codice

; Etichetta per le istruzioni
main:
    MOV cx, 5       ; sposta 5 in CX
    MOV AX, @data   ; carica l'indirizzo del segmento dati in AX
    MOV AX, 44B0    ; muove 44BO om AX
    MOV DS, AX      ; sposta il dato in AX nel DS (data segment)
    MOV AX, 0000    ; sposta 0000 in AX
    MOV AL, [0008]  ; sposta in AL la variabile nel DS:0008
    MOV BX, [0009]  ; sposta in BX la variabile nel DS:0009
    MOV SI, offset a; sposta in SI il puntatore di offset della variabile a in DS
    MOV CL, [SI]    ; sposta in CL il valore che corrisponde all'offset di SI in DS (DS:SI)
    MOV DX, [SI][1] ; sposta in DX il valore che corrisponde all'offset di SI aumentato di 1 (DS:SI+1)
    CALL increment  ; chiama l'istruzione definita dall'Etichetta increment | la prossima istruzione da eseguire andrà nello stack
                    ; in SS:FFFE c'è l'indirizzo della istruzione da eseguire dopo aver terminato l'esecuzione di increment (ovvero la nostra riga 26)
    
    ADD AX, BX ; aggiunge BX ad AX
    CMP AX, 1A0C ; controlla se il numero in AX è uguale a 1A0C e la ZF (zero flag sarà a 1 se ciò è vero)
    JE exit ; se la ZF è attiva per la vecchia istruzione allora jumpa all'indirizzo 002A

exit:
    MOV AH, 4ch ; coppia di istruzioni per terminare l'esecuzione del programma
    INT 20h

increment:
    ADD AX, 1 ;aggiungo 1 ad AX
    CALL do_nothing ; in SS:FFFC c'è l'indirizzo dell'istruzione da eseguire dopo aver finito l'esecuzione della funzione do_nothing (ovvero la riga 32)
    RET ; significa return (e fa poppare lo stack utilizzando l'indirizzo in storage per ricominciare ad eseguire il programma principale)

do_nothing:
    NOP ; non fa nulla
    RET