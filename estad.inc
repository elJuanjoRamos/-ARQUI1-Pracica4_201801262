COMPARAROPERACION MACRO buffer
LOCAL INICIO, GETPADRE, SALIR2, SALIR1, VERIFICAR, ENDF, REGRESAR, SIEXISTE, TERMINAR
    push CX
	push AX
	push SI
	push DI
	xor DI, DI
	xor SI, SI
	mov SI, 5
    MOV DI, 0
INICIO:
	CMP buffer[SI], '$'
	JE SALIR1
	MOV AL, buffer[SI]
	MOV padre[DI], AL
	INC SI
	INC DI
	JMP INICIO	
SALIR1:
    MOV SI,0

GETPADRE:

	CMP operaciones[SI], '['
	JE SALIR2
	INC SI
	JMP GETPADRE
SALIR2:

VERIFICAR:  
    MOV AL, padre[DI]
    CMP operaciones[SI], AL
    JNE REGRESAR
    INC SI
    INC DI
    CMP operaciones[SI], '$'
    JE ENDF
    
    CMP operaciones[SI], ':'
    JE SIEXISTE
    
    JMP VERIFICAR


SIEXISTE:
    print exitobusqueda
    INC SI
NUMERO:
    CMP operaciones[SI], ','
    JE TERMINAR
    printChar operaciones[SI]
    INC SI
    JMP NUMERO

REGRESAR:
    xor di, di
    MOV DI, 0
    INC SI
    JMP VERIFICAR

ENDF:
    print errorbusqueda
    print padre

TERMINAR:
    clear padre
ENDM

COMPARAREXIT MACRO buffer
LOCAL IGUAL, DIFERENTE
   
    xor CX, CX
    mov cx,4   ;Determinamos la cantidad de datos a leer/comparar
    mov AX,DS  ;mueve el segmento datos a AX
    mov ES,AX  ;Mueve los datos al segmento extra
    lea si, buffer                ; Reset pointer to arr1
    lea di, exit

    repe cmpsb  ;compara las dos cadenas
    je IGUAL ;Si fueron iguales
    jne DIFERENTE

    IGUAL:
        jmp MENUPRINCIPAL
    DIFERENTE:

ENDM



SHOWMEDIA MACRO buffer
LOCAL IGUAL, DIFERENTE
   
    xor CX, CX
    mov cx,10   ;Determinamos la cantidad de datos a leer/comparar
    mov AX,DS  ;mueve el segmento datos a AX
    mov ES,AX  ;Mueve los datos al segmento extra
    lea si, buffer                ; Reset pointer to arr1
    lea di, media

    repe cmpsb  ;compara las dos cadenas
    je IGUAL ;Si fueron iguales
    jne DIFERENTE

    IGUAL:
    ;MOV CX, 0
    
    
    print medias
        
    DIFERENTE:

ENDM



SHOWMEDIANA MACRO buffer
LOCAL IGUAL, DIFERENTE
   
    xor CX, CX
    mov cx,100   ;Determinamos la cantidad de datos a leer/comparar
    mov AX,DS  ;mueve el segmento datos a AX
    mov ES,AX  ;Mueve los datos al segmento extra
    lea si, buffer                ; Reset pointer to arr1
    lea di, mediana

    repe cmpsb  ;compara las dos cadenas
    je IGUAL ;Si fueron iguales
    jne DIFERENTE

    IGUAL:

        print medinas
    DIFERENTE:

ENDM

SHOWMODA MACRO buffer
LOCAL IGUAL, DIFERENTE
   
    xor CX, CX
    mov cx,9   ;Determinamos la cantidad de datos a leer/comparar
    mov AX,DS  ;mueve el segmento datos a AX
    mov ES,AX  ;Mueve los datos al segmento extra
    lea si, buffer                ; Reset pointer to arr1
    lea di, moda

    repe cmpsb  ;compara las dos cadenas
    je IGUAL ;Si fueron iguales
    jne DIFERENTE

    IGUAL:

        print modas
    DIFERENTE:

ENDM

