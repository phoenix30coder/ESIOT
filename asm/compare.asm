ORG 0H              ; Origin, start at address 0

MOV R2, #0x55    ; Load the first number into R0 (e.g., 0x55)
MOV R1, #0x55       ; Load the second number into R1 (e.g., 0x55)

MOV A, R1   
MOV B, R2        ; Move the value of R1 into the accumulator A
CJNE A, B, NOT_EQUAL ; Compare A with R0, jump to NOT_EQUAL if not equal

; If R0 == R1
SETB P1.0           ; Set P1.0 to 1 (indicating equality)
SJMP END            ; Jump to END

NOT_EQUAL:
CLR P1.0            ; Clear P1.0 to 0 (indicating inequality)

END:
SJMP END            ; End of program (infinite loop)

END                 ; End directive
