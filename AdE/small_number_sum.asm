.MODEL SMALL
.STACK 200H
.DATA
.CODE

START:

mov ax, 2       ; Move number 2 in ax
mov dx, ax      ; Move ax in dx

mov ax, 2       ; mvoe number 2 in ax

; Sum the number in dx with the number in ax storing the result in dx
add dx, ax      
; The values were hexadecimal so we have to "convert" them in numbers
add dx, '0'     

mov ah, 02h     ; Print char interrupt code
Int 21h         ; Run interrupt 21h

mov ah, 4ch     ; Exit program interrupt code
int 21h         ; Run interrupt 21h

END START
