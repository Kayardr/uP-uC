#include "Timer2.h"

#define 

void Timer2_Ini ( void ){
    /*Seleccion del preescalador y valor a almacenar en OCR2A*/

    /*Seleccion del RELOJ FUENTE*/

    /*Nuevos valores de TCNT2, OCR2x y TCCR2x*/

    /*Limpiar las banderas de interrupcion del Timer2*/

    /*Habilitar interrupciones*/
}

ISR(TIMER2_OVF_vect){
    TCNT2 = 252;
    mSecCnt++;
    if(!(mSecCnt%10000))
        SecFlag2 = 1;
}