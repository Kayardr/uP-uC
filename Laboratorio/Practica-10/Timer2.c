#include "Timer2.h"
#include <inttypes.h>
#include <avr/interrupt.h>
static volatile uint8_t n_value;
static volatile uint8_t SecFlag2;
static volatile uint32_t mSecCnt2;

void Timer2_Ini ( void ){
    /*Seleccion del preescalador y valor a almacenar en OCR2A*/
    TCCR2B |= (0b111 << CS20);
    uint8_t ocra_value = COMPARE_VALUE(FREC_CLK, 1024, 1);//Llenar esta parte
    n_value = 255 - ocra_value;
    /*Desabilitar interrupciones TC2*/
    TIMSK2 = 0;
    /*Seleccion del RELOJ FUENTE*/
    ASSR |= (1 << AS2);
    /*Nuevos valores de TCNT2, OCR2x y TCCR2x*/
    TCNT2 = 0;
    OCR2A = ocra_value;
    TCCR2A |= (1 << WGM21); 
    /*Limpiar las banderas de interrupcion del Timer2*/
    TIFR2 = 0;
    /*Habilitar interrupciones*/
    TIMSK2 |= (1 << TOIE2) | (1 << OCIE2A);
}

uint8_t Timer2_SecFlag( void ){
    if( SecFlag2 ){
        SecFlag2=0;
        return 1;
    }
    else{
        return 0;
    }
}

ISR(TIMER2_OVF_vect){
    TCNT2 = n_value;
    SecFlag2 = 1;
}

ISR(TIMER2_COMPA_vect){
    TCNT2 = n_value;
    SecFlag2 = 1;
}