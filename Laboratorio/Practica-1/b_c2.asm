.model tiny
	
 locals

.data
	messages	DB	"Introduceun cuatro digitos diferentes", 10, 13, '$'
	messageg	DB	"Adivina el numero", 10, 13, '$'
	secret 		DB	5, 0, 0, 0, 0, '$'
	guess 		DB	5, 0, 0, 0, 0, '$'
	lose		DB	"Lo siento, has perdido", 10, 13, '$'
	win			DB	"HAS GANADO!!!", 10, 13, '$'
	jline		DB 	10, 13, '$'

.code
	org 100h

main proc
	mov sp, 0fffh

	@@sigue:
	;========= Numero a adivinar ==========	
		mov dx, offset messages
		call prints
		mov dx, offset secret
		call read
	;======================================

		mov dx, offset messageg
		call prints
	
	;============= Adivinanza =============
		mov cx, 8
		@@try:
			call printn
			mov al, 09
			call print
			mov dx, offset guess
			call read
			mov dx, offset jline
			call prints
			
		;TO-DO
		;	Crear el procedimiento para evaluar si un numero esta correcto
		;	y si es asi terminar con el mensaje de victoria
		loop @@try
		;Derrota
		mov dx, offset lose
		call prints
		mov dx, offset jline
		call prints
	;======================================

	jmp @@sigue

	ret
	endp

;=============================================================
;	Procedimeintos
;=============================================================
	print proc
		push ax
		push dx

		mov dl, al
		mov ah, 2
		int 21h

		pop dx
		pop ax
		ret
	endp
	printn proc
		push ax
		push dx
		mov dx, 0
		mov dl, cl
		add dl, 30h
		mov ah, 02h
		int 21h

		pop dx
		pop ax
		ret
		endp

	prints proc
		push ax
		mov ah, 09h
		int 21h
		pop ax
		ret
		endp

	read proc
		push ax

		mov ah, 0ah
		int 21h

		pop ax
		ret
		endp
end main