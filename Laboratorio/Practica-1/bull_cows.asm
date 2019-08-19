.model tiny

   ;----- Insert INCLUDE "filename" directives here
   ;----- Insert EQU and = equates here
   
   locals
   
.data
      
      msgGet 	DB  'Introduce the secrete 4 digits:',10,13,0
	  msgBoard 	DB  'Bulls: ',9,'Cows: ',9,'Guesses:',10,13,0
	  msgGuess	DB 	'Guess the 4 digit sequence',10,10,13,0
	  msgWin	DB 	'You win!',10,10,13,0
	  msgLoose	DB 	'You LOOSE!',10,10,13,0
	  done		DB 	'Done.',10,13,0
	  new_line	DB 	10,13,0
	  secrete  	DB  5 dup(0)
	  guess    	DB  5 dup(0)

.code
            org 100h
	
;*************************************************************
;  Procedimiento principal
;*************************************************************	
	principal proc
            mov sp,0fffh	; inicializa SP (Stack Pointer)
			
		@@sigue:
			mov si, offset secrete 
			mov di, offset guess 
						
			mov dx, offset msgGet
			call puts
			mov dx,si
			call getDigits
			
			mov dx, offset done
			call puts
			mov dx, offset msgGuess
			call puts
			
			mov dx, offset msgBoard
			call puts

			mov cx, 8
		@@nextGuess:
			mov dx,di
			call getDigits
			call evalGuess
			call printHint
			mov dx, offset new_line
			call puts
			cmp al, 4					;Compara si los cuatro numeros son "BULL"
			jae @@msgWin 				;Si es asi, salta al mensaje de victoria
			loop @@nextGuess 			;Si no, comprueba que no se hayan terminado los intentos

			mov dx, offset msgLoose 	;Si ya no hay intentos
			call puts 					;Se despliega el mensaje de derrota
			jmp @@sigue

			@@msgWin:
			mov dx, offset msgWin
			call puts
		
			jmp @@sigue
			
			ret						; nunca se llega aquí
			endp

			
;***************************************************************
;  procedimientos
;***************************************************************            
    putchar	proc
			push ax
			push dx
			mov dl,al
			mov ah,2				; imprimir caracter DL
			int 21h					; usando servico 2 (ah=2)
			pop dx					; del int 21h
			pop ax
			ret
			endp
	
	getch	proc
			mov ah,8				; no echo
			int 21h				
			ret
			endp
	
	getche	proc
			mov ah,1				
			int 21h				
			ret
			endp
			
	puts	proc
			push ax
			push bx
			
			mov  bx,dx
		@@nxt: 
			mov  al,[bx]
			cmp  al,0
			je   @@end
			call putchar
			inc  bx
			jmp  @@nxt
			
		@@end: 
			pop  bx
			pop  ax
			ret
			endp
	
	getDigits proc
			push ax
			push bx
			push cx
			
			mov bx,dx
			mov cx,4
		@@gnxt: 
			call getch
			cmp al,'0'
			jb @@gnxt
			cmp al,'9'
			ja @@gnxt
			mov [bx],al
			inc bx
			loop  @@gnxt
			
			pop cx
			pop bx
			pop ax
			ret
			endp
	
	printHint proc
			push ax
			push dx
			
			add al,'0'
			call putchar ; print Bulls
			
			mov al,9
			call putchar ; tab
			
			mov al, ah
			add al,'0'
			call putchar ; print Cows
			
			mov al,9
			call putchar ; tab
			
			mov dx,di
			call puts
			
			pop dx
			pop ax
			ret
			endp

;***************************************************************
;  	Procedure that evaluates the Bulls (correct number in the correct place)
;  	and Cows (correct number but incorrect position) based on the two arrays
;	given by SI (secrete) and DI (guess).
;	Returns Bulls in AL, and Cows in AH	
;***************************************************************            
	evalGuess proc
			; place code here 
			push bx
			push cx
			push dx
			
			mov ax, 0
			mov cx, 0
			
			mov bx, si					;Asignamos a bx la direccion de los digitos a adivinar
		@@ndigit:
			mov dl, [bx]				;Leemos el primer digito
			push bx						;Salvamos la posicion de los digitos a adivinar

			mov bx, di					;Asignamos a bx la direccion de los digitos de intento
			mov ch, 0					;Reestablecemos ch a 0 cada que comparemos los digitos
										;	"Es el contador de los digitos adivinados"
		@@cmpdigit:
				mov dh, [bx]			;Leemos el digito adivinado

				cmp dl, dh				;Comparamos los digitos
				ja @@noeq				;	Si son iguales no saltamos
				jb @@noeq				;	Si no lo son saltamos
				cmp cl, ch				;Se compara si estan en la misma posicion
				ja @@cow				;	Si lo estan no saltamos
				jb @@cow				;	Si no, saltamos y asignamos a @@Cow
				inc al					;Si no saltamos incrementamos "Bulls"
				jmp @@endcmp
				@@cow:			
				inc ah					;Si saltamos incrementamos "Cows"
				jmp @@endcmp

				@@noeq:
				inc bx					;Se pasa al siguiente digito
				inc ch					;Se incrementa el contador de digitos
				cmp ch, 4				;Se compara la cantidad de digitos leidos con 4
				jb @@cmpdigit			;Si se han leido 4 se termina el ciclo
			@@endcmp:
			pop bx						;Se recupera bx
			inc bx						;Se lee el siguiente digito original
			inc cl						;Se incrementa su contador
			cmp cl, 4					;Se compara si la cantidad de digitos leidos es menos a 4
			jb @@ndigit					; de no ser asi se termina el ciclo

			pop dx						
			pop cx
			pop bx
			ret 						;Se retorna AX donde AL=Bulls y AH=Cows
			endp
						
end   principal              ; End of program 
