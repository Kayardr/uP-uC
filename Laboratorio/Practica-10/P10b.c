/*
    Uso de prueba para el TIMER del Tjuino
    Codificador: Ricardo Castañon Renteria
*/
#include <avr/io.h>
#include "Timer0.h"
#include "UART.h"
/* incluir lo necesario para usar UART0 */
//Defines
#define SetBitPort(port, bit) __asm__ ( "sbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit) )
#define ClrBitPort(port, bit) __asm__ ( "cbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit) )

void InitPorts(void);
int main(){
    /* llamar a función para inicializar puertos E/S */
    InitPorts();
    /* llamar a función para inicializar UART0 */
    UART_Init(0, 250000, 8, 3, 2, 0);
    Timer0_Ini(); /* Inicializar Timer0 para 1 sec.*/
    Timer2_Ini();
    while(1){ /* == main loop == */
        if( Timer0_SecFlag() ){ /* ¿ha pasado 1 Segundo? */
            
        /* instrucciones para encender LED */
            UART0_puts("1 segundo\n\r");
        /* instrucciones para apagar LED */
            //ClrBitPort(PORTF, 0);
        }
        if( Timer0_SecFlag2()){
            SetBitPort(PORTF, 0);
            gotoxy(10,4);
            setColor(32);
            UART0_puts("1 segundo");
            ClrBitPort(PORTF, 0);
        }
    }
    return 0;
}

void InitPorts(void){
    DDRF = 0xFF;
    PORTF = 0x00;
}
