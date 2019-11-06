.INCLUDE "m1280def.inc" ;Incluir definiciones de registros para 1280
.equ INIT_VALUE = 0		;Valor inicial R24
.equ A = 0x20
;=========== Inicializar ===============
ldi R24, INIT_VALUE
ldi R25, 0x20
;=========== Ciclo principal ===========
arriba:	inc 	R24
		cpi 	R24, 10
		breq	abajo
		rjmp 	PC-1
		rjmp	arriba

abajo:	dec 	R24
		cpi 	R24, 0
		breq	arriba
		rjmp 	abajo
