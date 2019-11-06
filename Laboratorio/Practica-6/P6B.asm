;Rutina de division y obtencion de residuo	;1
.INCLUDE "m1280def.inc"						;2
											;3
.def divid	= R21							;4
.def divis	= R22							;5
											;6
.def cosci	= R23							;7
.def resid	= R24							;8
											;9
.def decim 	= R25							;10
.def multi	= R27
.def aux	= R28							;11
											;12
ldi	divid, 0x04								;13
ldi divis, 0x03								;14
ldi decim, 0x02								;15
											;16
ldi cosci, 0x00								;17
ldi resid, 0x00								;18
ldi	aux,   0x00								;19
ldi multi, 0x0A								;20
											;21
cos:										;22
	cp		divid, divis					;23
	brlo 	cona							;24
	sub 	divid, divis					;25
	inc 	cosci							;26
	rjmp 	cos								;27
cona:										;28
	mul		divid, multi					;2
	mov		divid, R0
	mul		resid, multi
	mov		resid, R0					;30
	res:									;31
		cp		divid, divis				;32
		brlo 	conb
		sub 	divid, divis
		inc		aux
		rjmp 	res

	conb:
	add		resid, aux
	ldi		aux, 0
	dec 	decim
	cpi		decim, 0
	breq	fin
	rjmp cona
	
fin:
	out		PORTA, resid
	rjmp fin	
	

