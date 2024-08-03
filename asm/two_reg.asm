;program to transfer the data between two registers 

ORG 0000H      ; Origin, start at address 0000H
MOV R0, #55H 
MOV A,R0  ; Load immediate value 55H into register R0
MOV R1, A     ; Transfer the value from R0 to R1

HERE: SJMP HERE ; Infinite loop to end the program
END             ; End of the program
