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
    
endm








analizar macro buffer
LOCAL GETID , INICIO,  GETNUM, SALIR
    xor SI, SI
    XOR DI, DI
INICIO:
    mov AL, buffer[SI]
    cmp AL, '{'
    JE GETID
    cmp AL, '#'
    JE GETNUM

    CMP AL, '$'
    JE SALIR
    INC SI
    INC DI
    JMP INICIO
GETID:
    getIdentificador buffer, SI, DI
    INC SI
    INC DI
    JMP INICIO




GETNUM:
    INC SI
    PUSH DI
    xor DI, DI
    obtenerNumero buffer, SI, DI

    ;POP AX

    ;print AX
    
    JMP INICIO


SALIR:


endm

obtenerNumero macro buffer, indice, start
LOCAL INICIO, FIN, SALIR, SUMA, RESTA, MULTI, DIVI
MOV temporal[0], '$'
MOV temporal[1], '$'
MOV temporal[2], '$'
MOV temporal[3], '$'
MOV temporal[4], '$'
MOV temporal[5], '$'
INICIO:
    MOV AL, buffer[indice]
    CMP AL, ','
    JE FIN
    CMP AL, '}'
    JE FIN
    CMP AL, ']'
    JE FIN
    CMP AL, '['
    JE FIN
    CMP AL, '{'
    JE FIN
    MOV temporal[start], AL
    INC indice
    INC start
    JMP INICIO
FIN:
    mov SI, indice
    PUSH SI
    CovertirAscii temporal
    

    POP SI
    POP DI
    ;JMP INICIO


    mov bx,ax	
    POP AX

    cmp AX, '+'
    JE SALIR 
    cmp AX, '-'
    JE SALIR 
    cmp AX, '*'
    JE SALIR 
    cmp AX, '/'
    JE SALIR 

    
    PUSH AX
    POP CX
    POP AX
    cmp AX, '+'
    JE SUMA 
    cmp AX, '-'
    JE RESTA
    cmp AX, '*'
    JE MULTI
    cmp AX, '/'
    JE DIVI

    ;JMP INICIO


    ;JMP ENDF

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
	div bx
    JMP SALIR2


SALIR:
    PUSH AX
    push bx
    JMP ENDF
SALIR2:
    PUSH ax
    PUSH SI
    PUSH DI  
    ConvertirString resultado   
    print resultado
    POP DI
    POP SI
endm










insertarSimbolo macro char
    MOV AX, char
    PUSH AX
endm





getIdentificador macro buffer, INICIO, posicion
LOCAL SALIR, OBTENER, VERSUMA, VERRESTA,  VERMULTI, VERDIVI, INSERTAR1,INSERTAR2,INSERTAR3,INSERTAR4, GETMAS, GETMENOS, GETPOR, GETDIV
    INC INICIO
OBTENER:

    mov AL, buffer[INICIO]
    
    CMP AL, '{'
    JE SALIR
    CMP AL, '['
    JE SALIR
    CMP AL, 'a'
    JE VERSUMA
    CMP AL, 's'
    JE VERRESTA
    CMP AL, 'm'
    JE VERMULTI
    CMP AL, 'd'
    JE VERDIVI
    cmp AL, '+'
    JE GETMAS
    cmp AL, '-'
    JE GETMENOS
    cmp AL, '*'
    JE GETPOR
    cmp AL, '/'
    JE GETDIV

    MOV resultados[posicion], AL
    INC INICIO
    INC posicion
    JMP OBTENER


GETMAS:
    insertarSimbolo '+'
    INC INICIO
    INC posicion
    JMP OBTENER
GETMENOS:
    insertarSimbolo '-'
    INC INICIO
    INC posicion
    JMP OBTENER
GETPOR:
    insertarSimbolo '*'
    INC INICIO
    INC posicion
    JMP OBTENER
GETDIV:
    insertarSimbolo '/'
    INC INICIO
    INC posicion
    JMP OBTENER



VERSUMA:
    CMP buffer[INICIO +1], 'd'    
    JNE NOES
    CMP buffer[INICIO + 2], 'd'
    JNE NOES
    JMP INSERTAR1

VERRESTA:
    CMP buffer[INICIO +1], 'u'    
    JNE NOES
    CMP buffer[INICIO + 2], 'b'
    JNE NOES
    JMP INSERTAR2

VERMULTI:
    CMP buffer[INICIO +1], 'u'    
    JNE NOES
    CMP buffer[INICIO + 2], 'l'
    JNE NOES
    JMP INSERTAR3

VERDIVI:
    CMP buffer[INICIO +1], 'i'    
    JNE NOES
    CMP buffer[INICIO + 2], 'v'
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
    MOV AX, '+'
    PUSH AX
    JMP OBTENER
INSERTAR2:
    INC INICIO
    INC INICIO
    MOV AX, '-'
    PUSH AX
    JMP OBTENER

INSERTAR3:
    INC INICIO
    INC INICIO
    MOV AX, '*'
    PUSH AX
    JMP OBTENER

INSERTAR4:
    INC INICIO
    INC INICIO
    MOV AX, '/'
    PUSH AX
    JMP OBTENER


SALIR: 
    MOV resultados[posicion], ':'
    mov SI, INICIO
    mov DI, posicion
    

endm

