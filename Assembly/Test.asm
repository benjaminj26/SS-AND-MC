ASSUME CS:CODE, DS:DATA
DATA SEGMENT
MESSAGE1 DB "HELLO, WORLD$"
MESSAGE2 DB 0AH, "THIS IS FUN$"
DATA ENDS

CODE SEGMENT
START:
MOV AX, DATA
MOV DS, AX
MOV DX, OFFSET MESSAGE1
MOV AH, 09H
INT 21H
MOV DX, OFFSET MESSAGE2
MOV AH, 09H
INT 21H
MOV AH, 4CH
INT 21H
CODE ENDS
END START