

;======================= SECCION MACROS
include macros.inc
include archivo.inc
include ctrl.inc
include estad.inc
;=======================SECCION DE EJECUTABLE
.model small
.stack  
.data


;====================== SEGMENTO DE DATOS =================
;========== VARIABLES



encab         db 'UNIVERSIDAD DE SAN CARLOS DE GUATEMALA', 10,13,  'FACULTAD DE INGENIERIA',10,13, 'CIENCIAS Y SISTEMAS',10,13,'ARQUITECTURA DE COMPUTADORES Y ENSAMBLADORES', 10,13, 'JUAN JOSE RAMOS CAMPOS', 10,13, '201801262', 10,13,'SECCION:A',10,13, ' ',10,13, '1) Cargar Archivo',10,13,'2) Consola',10,13, '3) Salir', 10,13,10,13, 'Escoja Una opcion:','$'  
textoreporte  db  0ah, 0dh, '{', 0ah, 0dh, 'reporte:{', 0ah, 0dh


data    db   0ah, 0dh,'"alumno" : { "Nombre":"Juan Jose Ramos"' 
carnet  db   0ah, 0dh,'"Carnet":"201801262"' 
seccion db   0ah, 0dh,'"Seccion":"A"'
curso   db   0ah, 0dh,'"Curso":"Arquitectura de computadoras1"},'

opfecha db 0ah, 0dh,'"fecha" : {'
dia     db 0ah, 0dh,'"dia" :'
mes     db 0ah, 0dh,'"mes" :'
year     db 0ah, 0dh,'"año" :'
endfecha db 0ah, 0dh,'},'


ophora db 0ah, 0dh,'"hora" : {'
hora     db 0ah, 0dh,'"Hora" :'
minuto     db 0ah, 0dh,'"Minuto" :'
endhora db 0ah, 0dh,'},'
cerrar db 0ah, 0dh,'}'

openllave db '{',0ah,0dh

opres db ' : [',0ah,0dh
endres db 0ah, 0dh,']',0ah,0dh



final       db 10,13,'Gracias por usar la calculadora, vuelva pronto :) ',10,13, '$'


;=========== ARCHIVO
encabfile   db 10,13,'============= CARGAR ARCHIVO ===============', 10,13,'$'  
encabcons   db 10,13,'============= CONSOLA ===============', 10,13,'$'  

filepath    db 100 dup('$') ; ruta archivo
buffread    db 5000 dup('$') ; buffer lectura
buffwrite   db 200 dup('$') ; buffer escritura
handlefile  dw ?
comando     db 100 dup('$') ; comando

dia1    db 1 dup('$'), '$'
mes1    db 1 dup('$'), '$'
ano1    db 3 dup('$'), '$'
hora1   db 1 dup('$'), '$'
minuto1 db 1 dup('$'), '$'

media       db 'SHOW MEDIA', '$'
mediana     db 'SHOW MEDIANA', '$'
moda        db 'SHOW MODA', '$'
mayor       db 'SHOW MAYOR', '$'
menor       db 'SHOW MENOR', '$'
exit        db 'EXIT', '$'
Nombre      db 'nombre.txt','$'

textocorregido  db 5000 dup('$') ; 
operaciones     db 1000 dup('$'),'$' ; 
estadisticos    db 1000 dup('$'),'$' ; 
resultados      db 1000 dup('$'),'$' ; 
temporal        db 6 dup('$'),'$' ; 
temporal2       db 6 dup('$'),'$' ; 
resultado       db 100 dup('$')
padre           db 100 dup('$')
padretemporal   db 100 dup('$')
simbolo         db 1 dup('0')
OP1         db 'add', '$'
OP2         db 'sub', '$'
OP3         db 'div', '$'
OP4         db 'mul', '$'
OP5         db 'ADD', '$'
OP6         db 'SUB', '$'
OP7         db 'MUL', '$'
OP8         db 'DIV', '$'




msgOpenFile db 0ah,0dh, 'Ingrese el nombre de archivo: ', 32, '$'


msmError1 db 0ah,0dh,'Error al abrir archivo','$'
msmError2 db 0ah,0dh,'Error al leer archivo','$'
msmError3 db 0ah,0dh,'Error al crear archivo','$'
msmError4 db 0ah,0dh,'Error al Escribir archivo','$'


msmError5 db 0ah,0dh,'  ',0ah,0dh,'$'

msmError6 db 0ah,0dh,'--Elemento no encontrado: ',0ah,0dh,'$'

modas db 0ah,0dh,'-moda--',0ah,0dh,'$'
medias db 0ah,0dh,'-medias--',0ah,0dh,'$'
medinas db 0ah,0dh,'-medianas--',0ah,0dh,'$'

errorbusqueda db 0ah,0dh,'No se encuentra el resultado de: ','$'
exitobusqueda db 0ah,0dh,'El resultado es: ','$'



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
    clear   operaciones
    clear   resultado
    clear   resultados    
    xor SI, SI
    prueba1 textocorregido, SI
    jmp MENUPRINCIPAL

CONSOLA:
    print encabcons
    print msmError5
    
    printChar '>'
    printChar '>'
    clear comando
    getRuta2 comando
    COMPARAREXIT comando
    ;SHOWMODA comando
    ;SHOWMEDIANA comando
    ;SHOWMEDIA comando

    COMPARARPADRE comando
    COMPARAROPERACION comando
    



    jmp CONSOLA






















































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
