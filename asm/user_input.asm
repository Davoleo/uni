.MODEL SMALL
.STACK 200H
.DATA
.CODE

START:

mov ah, 01h     ; Get user input interrupt code
int 21h         ; Run interrupt 21h

mov bl, al      ; Transfer the input data stored in al into bl

mov dl, 10      ; 10 in ascii is new line
mov ah, 02h     ; Print char interrupt code
int 21h         ; Run interrupt 21h

mov dl, bl      ; Transfer user input form bl to dl
mov ah, 02h     ; Print user input data
int 21h         ; Run interrupt 21h



mov ah, 4ch     ; Exit program interrupt code 
int 21h         ; Run interrupt 21h

END START
