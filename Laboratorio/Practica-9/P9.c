#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
void InitPorts(void){
	DDRF  = 0b01111111;
  PORTF = 0b10000000;
}

char* romanb[] = {"(L)", "(X)(L)", "(X)", "(I)(X)", "(V)", "(I)(V)", "(I)", "C(I)", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
int div[] = {50000, 40000, 10000, 9000, 5000, 4000, 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

void itor(unsigned int number, char* str);

int main(void){
    char cad[20];
    uint16_t num;
    sei();
    UART_Init(0, 12345, 8, 1, 2);
    InitPorts();
    while(1){
          
        UART0_getchar();
        SetBitPort(PORTF, 1); 
        clrscr();
        gotoxy(2,2);
        setColor(YELLOW);                       //Definirlo en UART.h
        UART0_puts("Introduce un numero: ");
        setColor(GREEN);                        //Definirlo en UART.h
        UART0_gets(cad);
        num = UART0_atoi(cad);
        UART0_itoa(cad, num, 16);
        gotoxy(5, 3);
        setColor(BLUE);                         //Defnirlo en UART.h
        UART0_puts("Hex: ");
        UART0_puts(cad);

        UART0_itoa(cad, num, 2);
        gotoxy(5, 4);
        UART0_puts("Bin: ");
        UART0_puts(cad);

        itor(num, cad);
        gotoxy(5, 5);
        UART0_puts("Bin: ");
        UART0_puts(cad);
    }
    return 0;
}

void itor(unsigned int number, char* str){
	uint8_t k = 0;
  uint8_t l = 0;
	if(number==0){
		*str++ = 'n';
		*str = 0;
	}
	else{
		while(number){
			while(number/div[k]){
				for(l = 0; romanb[k][l]!=0; l++)
					*str++ = romanb[k][l];
				number -= div[k];
			}
			k++;
		}
		*str = 0;	
	}
}