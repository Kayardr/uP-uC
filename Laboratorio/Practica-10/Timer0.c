#include <avr/interrupt.h>
#include <inttypes.h>
#include "Timer0.h"
static volatile uint8_t SecFlag;
static volatile uint32_t mSecCnt;
void Timer0_Ini ( void ){
    TCNT0= 0; /* Inicializar valor para el timer0 */
    TCCR0A= (1 << WGM00); /* inicializa timer0 en modo 0 (normal) */
    OCR0A = 249;
    /* Inicializar con fuente de osc. Int. */
    TCCR0B=0x03; /* con Prescalador 64 */
    TIMSK0=0x01; /* habilita interrupcion del Timer0 */
    sei(); /* habilita interrupciones (global) */
}
uint8_t Timer0_SecFlag ( void ){
    if( SecFlag ){
        SecFlag=0;
        return 1;
    }
    else{
        return 0;
    }
}

ISR (TIMER0_OVF_vect){ /* TIMER0_OVF_vect */
    TCNT0+=0x06; /* reinicializar Timer0 sin perder conteo */
    mSecCnt++; /* Incrementa contador de milisegundos */
    if( !(mSecCnt%1000) ){
        SecFlag=1; /* Bandera de Segundos */
    }
    uint8_t i;
    for(i=0; i<DROPS_AMOUNT; i++){
        drops[i].millis--;
    }
}

uint32_t millis(void){return mSecCnt;}

void delay(uint16_t msWaitTime){
    uint32_t last = mSecCnt;
    while((mSecCnt - last) < msWaitTime);
}

//Funcion que registra un apuntador de funcion, la cul debera ser invocada al transcurrir n-segundos.
void MiliTimerRegister(void (*callback)(), uint16_t msWaitTime){
    uint32_t last = mSecCnt;
    while((last - mSecCnt) < msWaitTime)
        (*callback)();
}

void SecTimerRegister(void (*callback)(), uint16_t sWaitTime){
    while(sWaitTime){
        if(Timer0_SecFlag())
            sWaitTime--;
    }
    (*callback)();
}