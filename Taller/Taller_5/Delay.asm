.INCLUDE "m1280def.inc"

.equ	INIT_VALUE = 0x80

.equ	N1 = 0x02
.equ	N2 = 0x03
.equ	N3 = 0x00
ldi		R24, INIT_VALUE
out		DDRB, R24
;==========================================
;			Delay de 100us
nxt:
	call retraso
	call retraso2
	call retraso3
	out PINB, R24
	rjmp nxt

retraso:
ldi R31, 0x00	;h
ldi	R30, 0x9F	;l

ldi R18, N1

nxt1us:	
		dec 	R18
		brne 	nxt1us
		sbiw	R30, 1
		ldi		R18, N1
		brne 	nxt1us
		ret

;==========================================
;			Delay de 1ms
retraso2:
ldi R31, 0x04	;h
ldi	R30, 0xCE	;l

ldi R18, N2

nxtms:	
		dec 	R18
		brne 	nxtms
		sbiw	R30, 1
		ldi		R18, N2
		brne 	nxtms
		ret

;==========================================
;			Delay de 1s
retraso3:
ldi R31, 0xD3	;h
ldi	R30, 0xFE	;l

ldi R18, 0x30

nxts:	
		sbiw	R30, 1
		sbci	R18, 0
		brne nxts
		ret




