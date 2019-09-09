.model tiny
 	locals

.data

.code
	org 100h

;====================================================
;	Prototipes
;====================================================
	public _peek
	public _poke
	public _putchar
	public _getchar
;====================================================
;	Funciones
;====================================================
	_peek proc				;Get data on memory
		push bp
		mov bp, sp
		
		mov bx, [bp+6]		;offset
		push ds
		mov ds, [bp+4]		;data segment 2+2, por push e IP(se introduce automaticamente)
		mov al, [bx]		;data out
		
		pop ds
		pop bp
		ret
	endp

	_poke proc				;Put data in memory
		push bp
		mov bp, sp
		
		mov bx, [bp+6]		;offset
		push ds
		mov ds, [bp+4]		;data segment
		mov dl, [bp+8]		;data in
		mov [bx], dl		;in the ds*10h+bx put the data in

		pop ds
		pop bp
		ret
	endp

	_putchar proc
		push bp
		mov bp, sp
		mov dl, [bp+4]
		mov ah, 02h
		int 21h
		pop bp
		ret
	_putchar endp

	_getchar proc
		push bp
		mov bp, sp
		mov ah, 01h
		int 21h
		pop bp
		ret
	_getchar endp
END