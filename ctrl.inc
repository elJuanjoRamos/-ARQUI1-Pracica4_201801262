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
LOCAL EX, SALIR, CORREGIR, CAD, NUM, CAD1, CAD2

getSize buffer
EX:
    MOV AL, buffer[SI]
    
    cmp AL,'$'
    JE SALIR
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
    cmp AL, ','
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
    CMP buffer[SI], '#'
    JE NUM
    MOV textocorregido[DI], '"'
    INC DI
    JMP CAD

NUM:
    MOV textocorregido[DI], '#' 
    inc SI
    INC SI
    inc DI
    JMP EX
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
    MOV textocorregido[DI], '"'
    INC DI
    JMP EX
CORREGIR:
    MOV AL, buffer[SI]
    MOV textocorregido[DI], AL 
    INC DI
    INC SI
    JMP EX

SALIR:
    
endm





prueba1 macro buffer, indice
LOCAL INICIO, SALIR, CADENA
INICIO:
    MOV AL, buffer[indice]
    CMP AL, '"'
    JE CADENA
    cmp AL, '['
    JE SALIR

    inc indice
    JMP INICIO

CADENA: 
    INC indice
    XOR DI, DI
    getPadre buffer, indice, DI 
    INC indice
    JMP INICIO

SALIR:
    PUSH SI
    PUSH DI
    savepadre padre, operaciones
    POP DI
    POP SI
    ;limpiar resultados
    prueba buffer, indice
endm





prueba macro buffer, indice
LOCAL INICIO, FIN,CADENA, GETNUM
INICIO:
    MOV AL, buffer[indice]

    cmp AL, '$'
    JE SALIR
    CMP AL, '"'
    JE CADENA
    CMP AL, '#'
    JE GETNUM
    CMP AL, '}'
    JE GETENDTEMP



    inc indice
    JMP INICIO


CADENA:
    INC indice
    
    XOR DI, DI
    getIdentificador buffer, indice, DI
    INC indice
    JMP INICIO
GETNUM:
    INC indice
    xor DI, DI
    obtenerNumero buffer, indice, DI
    
    JMP INICIO

GETENDTEMP:
    INC indice
    CMP buffer[indice+1], '{'
    JE GETENDTEMP2
    CMP buffer[indice+1], ']'
    JE GETENDTEMP2
    JMP INICIO
GETENDTEMP2:
    INC indice
    PUSH SI
    PUSH DI
    saveopreciones resultados, resultado, operaciones
    
    POP DI
    POP SI
    JMP INICIO


SALIR:
endm









obtenerNumero macro buffer, indice, start
LOCAL INICIO, FIN, SALIR, SUMA, RESTA, MULTI, DIVI, SALIR2, INIT

INIT:
    MOV temporal[0], '$'
    MOV temporal[1], '$'
    MOV temporal[2], '$'
    MOV temporal[3], '$'
    MOV temporal[4], '$'
    MOV temporal[5], '$'
    JMP INICIO


INICIO:

    MOV AL, buffer[indice]
    CMP AL, ','
    JE FIN1
    CMP AL, '}'
    JE FIN1
    CMP AL, ']'
    JE FIN1
    CMP AL, '['
    JE FIN1
    CMP AL, '{'
    JE FIN1
    MOV temporal[start], AL
    INC indice
    INC start
    JMP INICIO
FIN1:
    
    mov SI, indice
    PUSH SI
    ;CONVIERTO A NUMERO EL NUMERO-CADENA
    evaluarNumero temporal
    POP SI
    PUSH AX
    JMP FIN
FIN:
    POP AX
    
    mov bx,ax	
    POP AX
    ; VERIFICO QUE SI LO QUE SACO ES SIMBOLO
    cmp AX, '+'
    JE SALIR 
    cmp AX, '-'
    JE SALIR 
    cmp AX, '*'
    JE SALIR 
    cmp AX, '/'
    JE SALIR 
    ;SI LO QUE HAY ES SIGNO, ME SALGO Y PUSHEO
    ; SI LO QUE HAY ES NYMERO, CONTINUA

    ;SIGNIFICA QUE SAQUE UN NUMERO
    ;EN LA PILA ESTABA:
    ;2
    ;3
    ;+

    PUSH AX
    POP CX
    POP AX
    ;SACO EL SIMBOLO Y MIRO QUE SIGNO ES DE AMBOS NUMEROS
    cmp AX, '+'
    JE SUMA 
    cmp AX, '-'
    JE RESTA
    cmp AX, '*'
    JE MULTI
    cmp AX, '/'
    JE DIVI


    JMP ENDF
    

SUMA:
    PUSH CX
    POP AX
    add ax, bx
    JMP SALIR2

RESTA:
    PUSH CX
    POP AX
    SUB ax, bx
    JMP SALIR2
MULTI:
    PUSH CX
    POP AX
    MUL bx
    JMP SALIR2

DIVI:
    PUSH CX
    POP AX

    xor dx,dx
	CWD
    idiv bx
    JMP SALIR2
SALIR:
    
    PUSH AX
    push bx
    JMP ENDF
SALIR2:
    PUSH ax
    PUSH SI

    ConvertirString resultado
    POP SI
    JMP FIN
ENDF:
endm





evaluarNumero macro buffer
LOCAL NEGAR, SALIR, NEGAR2, NEGAR3

    CMP buffer[0], '-'
    JE NEGAR
    CovertirAscii buffer
    JMP SALIR
NEGAR:
    MOV DI, 1
    JMP NEGAR2
NEGAR2:
    MOV AL, buffer[DI] 
    CMP AL, '$'
    JE NEGAR3
    mov temporal2[DI-1], AL
    INC DI
    JMP NEGAR2
NEGAR3:
    CovertirAscii temporal2
    not AX
    ADD AX, 1
    JMP SALIR
SALIR:
    clear temporal2

endm









insertarSimbolo macro char
    MOV AX, char
    PUSH AX
endm





getIdentificador macro buffer, INICIO, posicion
LOCAL SALIR, OBTENER, VERSUMA, VERSUMA2, VERRESTA, VERRESTA2,  VERMULTI, VERMULTI2, VERDIVI, VERDIVI2, INSERTAR1,INSERTAR2,INSERTAR3,INSERTAR4, GETMAS, GETMENOS, GETPOR, GETDIV, NOES, SALIR2
OBTENER:

    mov AL, buffer[INICIO] 
    CMP AL, '"'
    JE SALIR
    CMP AL, 'a'
    JE VERSUMA
    CMP AL, 'A'
    JE VERSUMA2
    CMP AL, 's'
    JE VERRESTA
    CMP AL, 'S'
    JE VERRESTA2
    CMP AL, 'm'
    JE VERMULTI
    CMP AL, 'M'
    JE VERMULTI2
    CMP AL, 'd'
    JE VERDIVI
    CMP AL, 'D'
    JE VERDIVI2
    cmp AL, '+'
    JE GETMAS
    cmp AL, '-'
    JE GETMENOS
    cmp AL, '*'
    JE GETPOR
    cmp AL, '/'
    JE GETDIV

    MOV resultados[posicion], AL
    INC SI
    INC posicion
    JMP OBTENER


GETMAS:
    insertarSimbolo '+'
    INC INICIO
    INC posicion
    JMP SALIR2
GETMENOS:
    insertarSimbolo '-'
    INC INICIO
    INC posicion
    JMP SALIR2
GETPOR:
    insertarSimbolo '*'
    INC INICIO
    INC posicion
    JMP SALIR2
GETDIV:
    insertarSimbolo '/'
    INC INICIO
    INC posicion
    JMP SALIR2



VERSUMA:
    CMP buffer[INICIO +1], 'd'    
    JNE NOES
    CMP buffer[INICIO + 2], 'd'
    JNE NOES
    JMP INSERTAR1

VERSUMA2:
    CMP buffer[INICIO +1], 'D'    
    JNE NOES
    CMP buffer[INICIO + 2], 'D'
    JNE NOES
    JMP INSERTAR1

VERRESTA:
    CMP buffer[INICIO +1], 'u'    
    JNE NOES
    CMP buffer[INICIO + 2], 'b'
    JNE NOES
    JMP INSERTAR2
VERRESTA2:
    CMP buffer[INICIO +1], 'U'    
    JNE NOES
    CMP buffer[INICIO + 2], 'B'
    JNE NOES
    JMP INSERTAR2

VERMULTI:
    CMP buffer[INICIO +1], 'u'    
    JNE NOES
    CMP buffer[INICIO + 2], 'l'
    JNE NOES
    JMP INSERTAR3

VERMULTI2:
    CMP buffer[INICIO +1], 'U'    
    JNE NOES
    CMP buffer[INICIO + 2], 'L'
    JNE NOES
    JMP INSERTAR3

VERDIVI:
    CMP buffer[INICIO +1], 'i'    
    JNE NOES
    CMP buffer[INICIO + 2], 'v'
    JNE NOES
    JMP INSERTAR4
VERDIVI2:
    CMP buffer[INICIO +1], 'I'    
    JNE NOES
    CMP buffer[INICIO + 2], 'V'
    JNE NOES
    JMP INSERTAR4

NOES:
    mov AL, buffer[INICIO]
    MOV resultados[posicion], AL
    inc posicion
    inc INICIO
    JMP OBTENER
INSERTAR1:
    INC INICIO
    INC INICIO
    INC INICIO
    MOV AX, '+'
    PUSH AX
    JMP SALIR2
INSERTAR2:
    INC INICIO
    INC INICIO
    INC INICIO
    MOV AX, '-'
    PUSH AX
    JMP SALIR2

INSERTAR3:
    INC INICIO
    INC INICIO
    INC INICIO
    XOR AX, AX
    MOV AX, '*'
    PUSH AX
    JMP SALIR2

INSERTAR4:
    INC INICIO
    INC INICIO
    INC INICIO
    MOV AX, '/'
    PUSH AX
    JMP SALIR2


SALIR:
    
    MOV resultados[posicion], ':'
    mov SI, INICIO
    mov DI, posicion

SALIR2:

endm






getPadre macro buffer, INICIO, posicion
LOCAL SALIR, OBTENER, SALIR2
OBTENER:
    mov AL, buffer[INICIO]
    CMP AL, '"'
    JE SALIR
    MOV padre[posicion], AL
    INC SI
    INC posicion
    JMP OBTENER
SALIR:
    MOV padre[posicion], '['
    mov SI, INICIO
    mov DI, posicion

SALIR2:

endm





clear macro buffer
LOCAL INICIO, SALIR
    PUSH DI 
    xor DI,DI
INICIO:
    CMP DI,300
    JE SALIR
    CMP buffer[DI], '$'
    JE SALIR
    
    MOV buffer[DI], '$'
    INC DI
    JMP INICIO
SALIR:
    XOR DI, DI
    POP DI
endm



