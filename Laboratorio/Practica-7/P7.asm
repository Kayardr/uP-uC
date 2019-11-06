.INCLUDE "m1280def.inc"

.equ	INIT_VALUE = 0x80
ldi		R24, INIT_VALUE
out		DDRB, R24

nxt:
	call	retraso1
	call	retraso2
	call 	retraso3
	rjmp 	nxt

retraso1:
	ldi R31, 0x01		;h
	ldi R30, 0x11		;l

	ldi	R18, 0x00

	nxtus:	nop
			sbiw	R30, 1
			sbci	R18, 0
			brne	nxtus
			ret

retraso2:
	ldi R31, 0xE1		;h
	ldi R30, 0xFE		;l

	ldi	R18, 0x04

	nxtms:
		sbiw	R30, 1
		sbci	R18, 0
		brne	nxtms
		ret

retraso3:
	ldi R31, 0xD3		;h
	ldi R30, 0xFE		;l

	ldi	R18, 0x30

	nxts:
		sbiw	R30, 1
		sbci	R18, 0
		brne	nxts
		ret
