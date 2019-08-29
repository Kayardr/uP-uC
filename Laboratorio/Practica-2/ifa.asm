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
		mov ah, 08h
		int 21h
		mov ah, 0
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