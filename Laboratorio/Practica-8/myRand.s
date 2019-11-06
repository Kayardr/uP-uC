 
.global myRand

myRand:
;pusR25 R0

ldi		R24, 0x22
ldi		R19, 0x1A
ldi		R20, 0xFF

ldi		R21, 0x10
ldi		R22, 0x27

ldi		R27, 0x05

;=================================
;		Aleatorios
;=================================
principal:
	;R25acer el algoritmo
	inc 	R24
	;Obtener r
	mul		R24, R19
	mov		R25, R1
	mov 	R26, R0
	mov		R23, R20
	;Obtener residuo
	call 	res
	
	;Contador
	cpi		R21, 0x1
	brlo	g
	dec		R21
	mov		R24, R26
	rjmp	principal

  g:cpi 	R22, 0x1
  	brlo	end
	dec 	R22
	ldi		R21, 0xff
	rjmp 	principal

end:
	mov 	R24, R24
	;pop 	R0
	ret

res:
	
	cp		R26, R23			;Comparar si parte baja es menor que el R23 
	brlo	b					; si lo es saltar b (operacion parte alta)
	sub		R26, R23			; si no, restar a parte baja el R23
	cpi		R25, 1				;Comparar si parte alta mayor o igual a 1
	brlo	ab					; si no se termina y retorna parte baja
	dec		R25					; si si se decrementa en uno part alta
	ldi		R26, 0xFF				; en la parte baja se carga el numero 255
	rjmp 	res					;Repetir la operacion	;
	ab:
	ret							;Terminar
b:
	cpi		R25, 1				;Comparar si parte alta mayor/igual a 1
	brlo	bb					; si no, retornar parte baja
	mov		R18, R23		; si si, salvar el R23
	sub		R18, R26				; restar al R18 la parte baja
	dec		R25					;Decrementar parte alta
	ldi		R26, 0xFF				;Cargar en parte baja 255
	sub		R26, R18				;Restar a parte baja el R18iliar
	inc 	R26					; compensar resultado sumando uno
	rjmp 	res					;Repetir operacion
	bb:
	ret							;Terminar
