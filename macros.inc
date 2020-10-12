
print macro cadena ; print-> id del macro; macro > reservada, cadena
MOV ah,09h
MOV dx,@data
MOV ds,dx
MOV dx, offset cadena
int 21h
endm        


getChar MACRO 
mov ah,01h
int 21h
endm


printChar macro char 
mov ah,02h
mov dl,char
int 21h
endm





;OBTENER FECHA
getfecha macro
    MOV AH,2AH
    INT 21H
endm

;OBTENER HORA
gethora macro
    MOV AH,2CH
    INT 21H
endm

;OBTENER FECHA
obtenerFechaHora macro dia, mes, ano, hora, minuto, segundo
    XOR AX,AX
    XOR BX,BX
    XOR CX,CX
    getfecha
    MOV BX,CX
    convertirString1 BX,ano
    XOR BX,BX
    getfecha
    MOV BL,DH
    convertirString1 BX,mes
    getfecha
    MOV BL,DL
    convertirString1 BX,dia
    XOR BX,BX
    gethora
    MOV BL,CH
    convertirString1 BX,hora
    gethora
    MOV BL,CL
    convertirString1 BX,minuto 
    gethora
    MOV BL,DH
    convertirString1 BX,segundo 
endm







ConvertirString macro buffer
	LOCAL Dividir,Dividir2,FinCr3,NEGATIVO,FIN2,FIN
	xor si,si
	xor cx,cx
	xor bx,bx
	xor dx,dx
	mov dl,0ah
	test ax,1000000000000000
	jnz NEGATIVO
	jmp Dividir2

	NEGATIVO:
		neg ax
		mov buffer[si],45
		inc si
		jmp Dividir2

	Dividir:
		xor ah,ah
	Dividir2:
		div dl
		inc cx
		push ax
		cmp al,00h
		je FinCr3
		jmp Dividir
	FinCr3:
		pop ax
		add ah,30h
		mov buffer[si],ah
		inc si
		loop FinCr3
		mov ah,24h
		mov buffer[si],ah
		inc si
	FIN:
endm


CovertirAscii macro numero
	LOCAL INICIO,FIN
	xor ax,ax
	xor bx,bx
	xor cx,cx
	mov bx,10	;multiplicador 10
	xor si,si
	INICIO:
		mov cl,numero[si] 
		cmp cl,48
		jl FIN
		cmp cl,57
		jg FIN
		inc si
		sub cl,48	;restar 48 para que me de el numero
		mul bx		;multplicar ax por 10
		add ax,cx	;sumar lo que tengo mas el siguiente
		jmp INICIO
	FIN:
endm





;CONVERTIR STRING
convertirString1 macro reg, buffer
    LOCAL Dividir, Dividir2, FINC3, Final
    XOR SI,SI       ; COLOCA A CERO LOS REGISTROS DEL SEGMENTO
    XOR CX,CX       ; COLOCA A CERO LOS REGISTROS DEL SEGMENTO
    XOR AX,AX       ; COLOCA A CERO LOS REGISTROS DEL SEGMENTO
    MOV AX,reg
    MOV dl,0ah
    JMP Dividir2

    Dividir:
        XOR AH,AH

    Dividir2:
        DIV DL
        INC CX
        PUSH AX
        CMP AL,00H
        JE FINC3
        JMP Dividir
    FINC3:
        POP AX
        ADD AH,30H
        MOV buffer[SI], AH
        INC SI
        LOOP FINC3
        INC SI
    Final:
endm

saveopreciones macro bufferOperacion, bufferResultado, bufferOperaciones
LOCAL INICIO, FIN, INSERTOPERATION,INSERTARRESULTADO1,INSERTARRESULTADO 
MOV SI, 0
MOV DI, 0
INICIO:
	CMP bufferOperaciones[SI], '$'
	JE INSERTOPERATION
	INC SI
	JMP INICIO

INSERTOPERATION:
	CMP bufferOperacion[DI], '$'
	JE INSERTARRESULTADO1
	MOV AL, bufferOperacion[DI]
	MOV bufferOperaciones[SI], AL
	INC SI
	INC DI
	JMP INSERTOPERATION

INSERTARRESULTADO1:
	xor DI, DI
	JMP INSERTARRESULTADO

INSERTARRESULTADO:
	CMP bufferResultado[DI], '$'
	JE FIN

	MOV AL, bufferResultado[DI]
	MOV bufferOperaciones[SI], AL
	INC SI
	INC DI
	JMP INSERTARRESULTADO

FIN:
MOV bufferOperaciones[SI], ','

clear bufferOperacion
clear bufferResultado
endm


savepadre macro bufferOperacion, bufferOperaciones
LOCAL INICIO, FIN, INSERTOPERATION, FIN2
MOV SI, 0
MOV DI, 0
INICIO:
	CMP bufferOperaciones[SI], '$'
	JE INSERTOPERATION
	INC SI
	JMP INICIO

INSERTOPERATION:
	CMP bufferOperacion[DI], '$'
	JE FIN
	MOV AL, bufferOperacion[DI]
	MOV bufferOperaciones[SI], AL
	INC SI
	INC DI
	JMP INSERTOPERATION

FIN:
	clear bufferOperacion
endm




COMPARARPADRE macro buffer   ;   MACRO QUE SE ENCARGA DE COMPARAR EL COMANDO EJECUTADO
LOCAL IGUAL, DIFERENTE, INICIO, SALIR1, SALIR2, GETPADRE, VERIFICAR, SALIR, ENDF, ENDF2
	push CX
	push AX
	push SI
	push DI
	xor DI, DI
	xor SI, SI
	mov SI, 5
INICIO:
	CMP buffer[SI], '$'
	JE SALIR1
	MOV AL, buffer[SI]
	MOV padre[DI], AL
	INC SI
	INC DI
	JMP INICIO	
SALIR1:
	xor SI, SI
	xor DI, DI
	MOV SI, 0
	MOV DI, 0
GETPADRE:

	CMP operaciones[SI], '['
	JE SALIR2
	MOV AL, operaciones[SI]
	MOV padretemporal[DI], AL
	INC SI
	INC DI
	JMP GETPADRE

SALIR2:
	xor DI, DI
	xor SI, SI
	MOV SI, 0
	MOV DI, 0
	JMP VERIFICAR	

VERIFICAR:
	MOV AL, padretemporal[SI]
	cmp padre[SI], AL
	JNE ENDF
	CMP AL, '$'
	JE ENDF2
	INC SI
	INC DI
	JMP VERIFICAR
ENDF:
	JMP SALIR
ENDF2:
	
	imprimir
	getChar

	JMP SALIR
SALIR:
		POP DI
		POP SI
		POP AX
		POP CX
endm



imprimir macro 
	getRuta filepath
	createFile filepath,handlefile
	openFile filepath, handlefile
	writeFile SIZEOF textoreporte, textoreporte, handlefile
	writeFile SIZEOF data, data, handlefile
	writeFile SIZEOF carnet, carnet, handlefile
	writeFile SIZEOF seccion, seccion, handlefile
	writeFile SIZEOF curso, curso, handlefile

	obtenerFechaHora dia1, mes1, ano1, hora1, minuto1

	writeFile SIZEOF opfecha, opfecha, handlefile
	writeFile SIZEOF dia, dia, handlefile
	writeFile SIZEOF dia1, dia1, handlefile
	writeFile SIZEOF mes, mes, handlefile
	writeFile SIZEOF mes1, mes1, handlefile
	writeFile SIZEOF year, year, handlefile	
	writeFile SIZEOF ano1, ano1, handlefile
	writeFile SIZEOF endfecha, endfecha, handlefile


	writeFile SIZEOF ophora, ophora, handlefile
	writeFile SIZEOF hora, hora, handlefile
	writeFile SIZEOF hora1, hora1, handlefile
	writeFile SIZEOF minuto, minuto, handlefile
	writeFile SIZEOF minuto1, minuto1, handlefile
	writeFile SIZEOF endhora, endhora, handlefile


	
PRINTPADRE:
	PUSH AX
	PUSH DI
	mov simbolo[0], '"'
	writeFile SIZEOF simbolo, simbolo, handlefile

	MOV AL, '0'
	MOV DI, 0
	jmp PRINTPADRE2

PRINTPADRE2:
	MOV AL, padre[DI]
	CMP AL, '$'
	JE SEGUIR
	INC DI
	mov simbolo[0], AL
	writeFile SIZEOF simbolo, simbolo, handlefile
	JMP PRINTPADRE2


SEGUIR:
	mov simbolo[0], '"'
	writeFile SIZEOF simbolo, simbolo, handlefile

	POP DI
	POP AX
	writeFile SIZEOF opres, opres, handlefile


	imprimirOperaciones

	writeFile SIZEOF endres, endres, handlefile
	writeFile SIZEOF cerrar, cerrar, handlefile
	writeFile SIZEOF cerrar, cerrar, handlefile

	closeFile handlefile
	getChar

endm


imprimirOperaciones macro
LOCAL INICIO, SALIR, INTERIOR, OPER, OPERI, DOSPUNTOS

INICIO:
	PUSH CX
	push AX
	push SI
	push DI
	
	MOV AL, '0'
	MOV DI, 0
INTERIOR:
	CMP operaciones[DI], '['
	JE OPERI
	INC DI
	JMP INTERIOR
OPERI:
	
	writeFile SIZEOF openllave, openllave, handlefile
	mov simbolo[0], '"'
	writeFile SIZEOF simbolo, simbolo, handlefile

	inc DI
	JMP OPER
OPERI2:
	;INC DI
	writeFile SIZEOF endhora, endhora, handlefile
	CMP operaciones[DI], '$'
	JE SALIR
	JMP OPERI
OPER:
	MOV AL, operaciones[DI]
	CMP AL, ','
	JE OPERI2
	CMP AL, ':'
	JE DOSPUNTOS
	
	CMP AL, '$'
	JE SALIR
	INC DI
	mov simbolo[0], AL
	writeFile SIZEOF simbolo, simbolo, handlefile
	JMP OPER
DOSPUNTOS:
	INC DI
	mov simbolo[0], '"'
	writeFile SIZEOF simbolo, simbolo, handlefile
	mov simbolo[0], ':'
	writeFile SIZEOF simbolo, simbolo, handlefile
	
	JMP OPER
SALIR:
	mov DI, 0
	MOV SI, 0	
	POP DI
	POP SI
	POP AX
	POP CX
endm


COMPARARMEDIANA macro buffer   ;   MACRO QUE SE ENCARGA DE COMPARAR EL COMANDO EJECUTADO
LOCAL IGUAL, DIFERENTE
	push CX
	push AX
	push SI
	push DI
    xor CX, CX
    mov cx,12   ;Determinamos la cantidad de datos a leer/comparar
    mov AX,DS  ;mueve el segmento datos a AX
    mov ES,AX  ;Mueve los datos al segmento extra
    lea si, buffer                ; Reset pointer to arr1
    lea di, mediana
    repe cmpsb  ;compara las dos cadenas
    je IGUAL ;Si fueron iguales
    jne DIFERENTE

    IGUAL:
        mostrarmediana
    DIFERENTE:
        MOV cx, 12
		POP DI
		POP SI
		POP AX
		POP CX
endm


mostrarmedia macro
	print medias
endm




mostrarmoda macro
	print modas
endm


mostrarmediana macro
	print medianas
endm