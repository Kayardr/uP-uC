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
	_peek proc
		push bp
		push ds

		mov bp, sp
		
		mov ds, [bp+4]
		mov bx, [bp+8]
		mov ax, [bx]
		
		pop ds
		pop bp
		ret
	endp

	_poke proc
		push bp
		push ds
		push bx
		push ax
		mov bp, sp

		mov ds, [bp+4]
		mov bx, [bp+8]
		mov ax, [bp+12]

		mov [bx], ax

		pop ax
		pop bx
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