.MODEL SMALL
.STACK 200H

.DATA
msg db "Hello World!$"  ; db is the bytes initializaotion

.CODE

START:

MOV dx, OFFSET msg      ; Move into dx the message offset
MOV ax, SEG msg         ; Move into ax the message segmet
MOV ds, ax              ; Move ax into ds

MOV ah, 09              ; Print string interrupt code
Int 21h                 ; Run 21h interrupt

mov ah, 4ch             ; Exit program interrupt code
int 21h                 ; Run 21h interrupt

END START