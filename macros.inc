
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
print msmError5
print bufferOperaciones

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
	print bufferOperaciones
	clear bufferOperacion
endm