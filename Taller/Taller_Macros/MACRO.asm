.INCLUDE "m1280def.inc"

ldi		r20, 0xA5			;A5 en la parte baja
ldi		r21, 0x5A			;5A en la parte alta

;Funncion de shift logico a la derecha
.MACRO SHR16				;Recibe como parametro una constante 16 => r =< 24 y r =< 28
	clr		r27				;Limpio la parte alta de X
	ldi		r26, @0			;Cargo el parametro en x bajo
	ld		r20, X+			;Cargo el dato almacenado en la posicion apuntada por x bajo
	ld 		r21, X			;Cargo el dato almacenado en la posicion apuntada po x alto
	
	LSR		r21				;Shift logico derecho sobre parte alta del dato
	ROR		r20				;Rotacion derecha con carry sobree la parte baja del dato

	st		X, R21			;Almaceno de forma indirecta la parte alta en la posicion apuntada por x alto
	st		-X, r20			;Almaceno de forma indirecta la parte alta en la posicion apuntada por x bajo
	
.ENDM

;Funncion de shift logico a la izquierda
.MACRO SHL16				;Recibe como parametro una constante 16 => r =< 24 y r =< 28
	clr		r27				;Limpio la parte alta de X
	ldi		r26, @0			;Cargo el parametro en x bajo
	ld		r20, X+			;Cargo el dato almacenado en la posicion apuntada por x bajo
	ld 		r21, X			;Cargo el dato almacenado en la posicion apuntada po x alto
	
	LSL		r20				;Shift logico izquierdo sobre parte baja del dato
	ROL		r21				;Rotacion izquierda con carry sobree la parte alta del dato

	st		X, R21			;Almaceno de forma indirecta la parte alta en la posicion apuntada por x alto
	st		-X, r20			;Almaceno de forma indirecta la parte alta en la posicion apuntada por x bajo
.ENDM

SHR16	20 		
SHL16	20

