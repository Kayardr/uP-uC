#include <avr/interrupt.h>
#include <inttypes.h>
static volatile uint8_t SecFlag;
static volatile uint8_t SecFlag2;
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

uint8_t Timer0_SecFlag2 ( void ){
    if( SecFlag2 ){
        SecFlag2=0;
        return 1;
    }
    else{
        return 0;
    }
}
ISR (TIMER0_OVF_vect){ /* TIMER0_OVF_vect */
    
    TCNT0+=0x06; /* reinicializar Timer0 sin perder conteo */
    //mSecCnt++; /* Incrementa contador de milisegundos */
    if( !(mSecCnt%1000) ){
        SecFlag=1; /* Bandera de Segundos */
    }
}

//Revisar el documento para configuracion del modo asincrono del Timer
void Timer2_Ini ( void ){
    TCNT2 = 0;
    TCCR2A = (1 << WGM21);
    OCR2A = 3;                  //4.096
    TCCR2B = 0x02;
    ASSR |= (1 << AS2) | (1 << EXCLK);
    
    TIMSK2 = 0x01;
}

uint32_t millis(void){return mSecCnt;}

void delay(void){
    uint8_t i = 0;
    i++;
}

ISR(TIMER2_OVF_vect){
    TCNT2 = 252;
    mSecCnt++;
    if(!(mSecCnt%10000))
        SecFlag2 = 1;
}
