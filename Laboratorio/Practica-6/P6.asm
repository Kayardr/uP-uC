;Practica 6
.INCLUDE "m1280def.inc"

.def semilla	= R26
.def constan	= R27
.def modulo		= R28

.def count_l	= R21
.def count_h	= R22
.def divisor	= R23
.def aux		= R24

.def h			= R16
.def l 			= R17
.def count		= R18

ldi		semilla, 0x22
ldi		constan, 0x12
ldi		modulo, 0xFF

ldi		count_l, 0x10
ldi		count_h, 0x27

ldi		count, 0x00

;=================================
;		Aleatorios
;=================================
principal:
	;Hacer el algoritmo
	out 	PORTA, semilla
	inc 	semilla
	;Obtener r
	mul		semilla, constan
	mov		h, R1
	mov 	l, R0
	mov		divisor, modulo
	;Obtener residuo
	call 	res
	
	;Contador
	cpi		count_l, 0x1
	brlo	g
	dec		count_l
	mov		semilla, l
	
	rjmp	principal

  g:cpi 	count_h, 0x1
  	brlo	end
	dec 	count_h
	ldi		count_l, 0xff
	rjmp 	principal

end:
	rjmp end

res:
	
	cp		l, divisor			;Comparar si parte baja es menor que el divisor 
	brlo	b					; si lo es saltar b (operacion parte alta)
	sub		l, divisor			; si no, restar a parte baja el divisor
	cpi		h, 1				;Comparar si parte alta mayor o igual a 1
	brlo	ab					; si no se termina y retorna parte baja
	dec		h					; si si se decrementa en uno part alta
	ldi		l, 0xFF				; en la parte baja se carga el numero 255
	rjmp 	res					;Repetir la operacion	;
	ab:
	ret							;Terminar
b:
	cpi		h, 1				;Comparar si parte alta mayor/igual a 1
	brlo	bb					; si no, retornar parte baja
	mov		aux, divisor		; si si, salvar el divisor
	sub		aux, l				; restar al aux la parte baja
	dec		h					;Decrementar parte alta
	ldi		l, 0xFF				;Cargar en parte baja 255
	sub		l, aux				;Restar a parte baja el auxiliar
	inc 	l					; compensar resultado sumando uno
	rjmp 	res					;Repetir operacion
	bb:
	ret							;Terminar

	

			

