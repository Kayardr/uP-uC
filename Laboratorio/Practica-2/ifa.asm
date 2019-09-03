.model tiny
	locals
.data

.code
	org 100h

;====================================================
;	Headers
;====================================================
	public _getchar
	public _putchar

;====================================================
;	Funciones
;====================================================
	_getchar proc
		push bp
		mov bp, sp
		mov ah, 01h
		int 21h
		pop bp
		ret
	_getchar endp


	_putchar proc
		push bp
		mov bp, sp
		mov dl, [bp+4]
		mov ah, 02h
		int 21h
		pop bp
		ret
	_putchar endp
END