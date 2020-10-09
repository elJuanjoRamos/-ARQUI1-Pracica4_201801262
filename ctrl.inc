getSize macro buffer
LOCAL INICIO, LIMPIAR
XOR SI,SI   ;Seteamos los registros SI AX Y CX A 0
XOR CX,CX
XOR AX,AX
LEA SI,[buffer] ;Movemos la palabra a si
INICIO:
    LODSB ;Extraemos el ultimo caracter en AL
    CMP AL,'$' ;SI ES IGUAL A 0 SE ACABO LA PALABRA
    JE LIMPIAR
    INC CX    ;INCREMENTAMOS EL CONTADOR
    JMP INICIO  ;volvemos al bucle
LIMPIAR:;CONTADOR TENDRA LA LONGITUD DEL ARCHIVO
    xor si, si
    xor di, di

endm



limpiar macro buffer
LOCAL EX, SALIR, CORREGIR, CAD

getSize buffer
EX:
    cmp si,CX
    JE SALIR
    MOV AL, buffer[SI]
    cmp AL, '['
    JE CORREGIR
    cmp AL, ']'
    JE CORREGIR
    cmp AL, '{'
    JE CORREGIR
    cmp AL, '}'
    JE CORREGIR
    cmp AL, '#'
    JE CORREGIR
    cmp AL, '+'
    JE CORREGIR
    cmp AL, '*'
    JE CORREGIR
    cmp AL, '-'
    JE CORREGIR
    cmp AL, '/'
    JE CORREGIR
    cmp AL, '"'
    JE CAD1
    cmp AL, '0'
    JE CORREGIR
    cmp AL, '1'
    JE CORREGIR
    cmp AL, '2'
    JE CORREGIR
    cmp AL, '3'
    JE CORREGIR
    cmp AL, '4'
    JE CORREGIR
    cmp AL, '5'
    JE CORREGIR
    cmp AL, '6'
    JE CORREGIR
    cmp AL, '7'
    JE CORREGIR
    cmp AL, '8'
    JE CORREGIR
    cmp AL, '9'
    JE CORREGIR
    
    INC SI
    JMP EX
CAD1:
    INC SI
    JMP CAD
CAD:
    MOV AL, buffer[SI]
    CMP AL, '"'
    JE CAD2
    MOV textocorregido[DI], AL 
    INC DI
    INC SI
    JMP CAD
CAD2:
    INC SI
    JMP EX
CORREGIR:
    MOV AL, buffer[SI]
    MOV textocorregido[DI], AL 
    INC DI
    INC SI
    JMP EX

SALIR:
    ;print textocorregido
endm








analizar macro buffer 
    getSize buffer
    ;mov AL, CX
    mov sizecadena[0], CX
    ;mov sizecadena[50], Ch

    print sizecadena
endm