#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
 
ring_buffer_t RX;   //Buffer de entrada
ring_buffer_t TX;   //Buffer de salida

//USART0_RX_vect en iomx0.h (Arduino)

uint8_t UART_avalaible(){
    return(!BUFFER_FULL(RX));
}

void UART_Init(uint8_t com, uint32_t baudrate, uint8_t size, uint8_t parity, uint8_t stop, uint8_t U2X){
    //REGISTROS UART
    uint8_t* UCSRA = (uint8_t*)0xC0 + (8 * com);
    //Configuracion de UBRR
    uint16_t UBRR;
    if(U2X==0)
        UBRR = (FOSC / 16 / baudrate) - 1;
    else
        UBRR = (FOSC / 8 / baudrate) - 1;
    *(UCSRA + 5) = (uint8_t)(UBRR>>8);
    *(UCSRA + 4) = (uint8_t)UBRR;
    
    *(UCSRA) |= (U2X << U2X0);
    *(UCSRA + 1) |= 0xB8;
    //COnfiguracion del tamanio
    switch(size){
        case 5 : *(UCSRA + 2) &= ~(0b11 << UCSZ00);
            break;
        case 6 : *(UCSRA + 2) |= (0b01 << UCSZ00);
            break;
        case 7 : *(UCSRA + 2) |= (0b10 << UCSZ00);
            break;
        case 8 : *(UCSRA + 2) |= (0b11 << UCSZ00);
            break;
        case 9 : *(UCSRA + 2) |= (0b11 << UCSZ00);
                *(UCSRA + 1) |= (0b01 << UCSZ02);
            break;
        default :
            break;
    }
    //Configuracion de UCSRnC (Paridad)
    switch (parity){
    case 0 : *(UCSRA + 2) &= ~(0b11 << UPM00);
        break;
    case 1 : *(UCSRA + 2) |= (0b01 << UPM00);
        break;
    case 2 : *(UCSRA + 2) |= (0b10 << UPM00);
        break;
    case 3 : *(UCSRA + 2) |= (0b11 << UPM00);
    default:
        break;
    }
    //Configuracion de UCSRnC (paro)
    switch (stop){
    case 1: *(UCSRA + 2) &= ~(1 << USBS0);
        break;
    case 2: *(UCSRA + 2) |= (1 << USBS0);
    default:
        break;
    }

    RX.in_idx = 0;
    RX.out_idx = 0;
    TX.in_idx = 0;
    TX.out_idx = 0;
}

void UART_putchar(char data){
    while(BUFFER_FULL(TX));
    
    TX.out_idx = MOD(TX.out_idx+1);
    TX.buffer[TX.out_idx] = data;
    UCSR0B |= (1<<UDRIE0);
}

char UART0_getchar(void){
    char data;
    while ((UART_avalaible()));
    RX.in_idx = MOD(RX.in_idx+1);
    data = RX.buffer[RX.in_idx];
    UART_putchar(data);
    return data;
}

void UART0_puts(char *str){
    while(*str) UART_putchar(*str++);
}

void UART0_gets(char *str){
    const char *const aux = str;
    char c;
	c = UART0_getchar();
	while((c!=13)){
		if(c==8){
			if(str!=aux){
				UART_putchar(' ');
				UART_putchar(c);
				str--;
			}
			else
				UART_putchar(' ');
		}
		else if(str >= aux+20-1){
			UART_putchar(8);
			UART_putchar(' ');
			UART_putchar(8);
		}
		else
			*(str++)=c;
		c=UART0_getchar();
	}
    UART_putchar('\r');
    UART_putchar('\n');
	*(str) = '\0';
}

void UART0_itoa(char* str, uint16_t number, uint8_t base){
    char aux[20];
	int i=0;
	do{
		*(aux + i++) = (number % base) > 9 ? (number % base) + 55 : (number % base) + '0';
		number = number/base;
	}while(number > 0);
	while(i>0){
		*(str++) = *(aux + (--i));
	}
	*(str) = 0;
}

uint16_t UART0_atoi(char *str){
    if(*str){
		uint16_t count = 0;
		while(*str>='0' && *str<='9'){
			count = (count*10)+((*(str++))-'0');
		}
		return count;
	}
	return 0;
}

void clrscr(void){
    UART0_puts("\x1b[2J\x1b[H");
}

void setColor(uint8_t color){
    UART0_puts("\x1b[0");
    UART_putchar(color/10 + '0');
    UART_putchar(color%10 + '0');
    UART0_puts("m");
}

void gotoxy(uint8_t x, uint8_t y){
    char aux[4];
    UART0_puts("\033[");
    UART0_itoa(aux, y, 10);
    UART0_puts(aux);
    UART_putchar(';');

    UART0_itoa(aux, x, 10);
    UART0_puts(aux);
    UART_putchar('H');
}

ISR(USART0_UDRE_vect){
    //Esperar a que el buffer de transferencia este vacio
    if(BUFFER_EMPTY(TX)){
        
        //Se coloca el dato en el registro de datos
        UCSR0B &= ~( 1 << UDRIE0);
        //*(UCSRA) &= ( 1 << TXC0); 
    }else{                      //Se apaga la interrupcion
        TX.in_idx = MOD(TX.in_idx+1);
        UDR0 = TX.buffer[TX.in_idx];
    }
}

ISR(USART0_RX_vect){
    if(!BUFFER_FULL(RX)){
        RX.out_idx = MOD(RX.out_idx+1);
        RX.buffer[RX.out_idx] = UDR0;
    }
}

