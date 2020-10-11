

;======================= SECCION MACROS
include macros.inc
include archivo.inc
include ctrl.inc

;=======================SECCION DE EJECUTABLE
.model small
.stack  
.data


;====================== SEGMENTO DE DATOS =================
;========== VARIABLES



encab       db 'UNIVERSIDAD DE SAN CARLOS DE GUATEMALA', 10,13,  'FACULTAD DE INGENIERIA',10,13, 'CIENCIAS Y SISTEMAS',10,13,'ARQUITECTURA DE COMPUTADORES Y ENSAMBLADORES', 10,13, 'JUAN JOSE RAMOS CAMPOS', 10,13, '201801262', 10,13,'SECCION:A',10,13, ' ',10,13, '1) Cargar Archivo',10,13,'2) Consola',10,13, '3) Salir', 10,13,10,13, 'Escoja Una opcion:','$'  
final       db 10,13,'Gracias por usar la calculadora, vuelva pronto :) ',10,13, '$'


;=========== ARCHIVO
encabfile   db 10,13,'============= CARGAR ARCHIVO ===============', 10,13,'$'  
encabcons   db 10,13,'============= CONSOLA ===============', 10,13,'$'  

filepath    db 100 dup('$') ; ruta archivo
buffread    db 5000 dup('$') ; buffer lectura
buffwrite   db 200 dup('$') ; buffer escritura
handlefile  dw ?
comando    db 100 dup('$') ; comando


textocorregido  db 5000 dup('$') ; 
operaciones     db 1000 dup('$'),'$' ; 
resultados      db 1000 dup('$'),'$' ; 
temporal        db 6 dup('$'),'$' ; 
resultado       db 100 dup('$')
padre           db 100 dup('$')

OP1         db 'add', '$'
OP2         db 'sub', '$'
OP3         db 'div', '$'
OP4         db 'mul', '$'
OP5         db 'ADD', '$'
OP6         db 'SUB', '$'
OP7         db 'MUL', '$'
OP8         db 'DIV', '$'




msgOpenFile db 0ah,0dh, 'Ingrese el nombre de archivo: ', 32, '$'


;msmError1 db 0ah,0dh,'Error al abrir archivo','$'
msmError1 db 0ah,0dh,'---',0ah,0dh,'$'
msmError2 db 0ah,0dh,'Error al leer archivo','$'
msmError3 db 0ah,0dh,'Error al crear archivo','$'
msmError4 db 0ah,0dh,'Error al Escribir archivo','$'

msmError5 db 0ah,0dh,'  ',0ah,0dh,'$'

msmError6 db 0ah,0dh,'ERROR ERROR',0ah,0dh,'$'




;======================= SEGMENTO CODIGO ==================
.code
main proc
    MENUPRINCIPAL:
    print encab
    getChar
    cmp al,'1' 
    je CARGAR
    cmp al,'2'
    je CONSOLA
    cmp al,'3'
    je ENDGAME
    jmp MENUPRINCIPAL


;========== ARCHIVO


CARGAR:
    print encabfile
    print msgOpenFile
    getRuta filepath
    openFile filepath, handlefile

    readFile SIZEOF buffread,buffread,handlefile

    limpiar buffread
    ;clear   operaciones
    ;clear   resultado
    ;clear   resultados    
    print textocorregido
    print msmError5
    print msmError5
    
    xor SI, SI
    prueba1 textocorregido, SI
    jmp ENDGAME

CONSOLA:
    print encabcons
    printChar '>'
    printChar '>'
    getRuta comando






    jmp ENDGAME






















































ErrorAbrir:
	print msmError1
	getChar
	jmp MENUPRINCIPAL
ErrorLeer:
	print msmError2
	getChar
	jmp MENUPRINCIPAL
ErrorCrear:
	print msmError3
	getChar
	jmp MENUPRINCIPAL
ErrorEscribir:
	print msmError4
	getChar
	jmp MENUPRINCIPAL


ENDGAME:
    print final
    mov ah,4ch
    int 21h

main endp
end
