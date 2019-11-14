#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
void InitPorts(void){
	DDRF  = 0b01111111;
  PORTF = 0b10000000;
}
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
        UART0_puts("Introduce un numer carlie was here !!!!o");
        gotoxy(22, 2);
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
    }
    return 0;
}
