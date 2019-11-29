#ifndef _TIMER0_H
#define _TIMER0_H
#include <inttypes.h>
    #define DROPS_AMOUNT  30       //Cantidad de gotas a mostrar
    typedef struct drop_s{
        uint16_t x_pos;
        uint8_t y_pos;
        uint8_t size;
        uint8_t state;
        uint8_t millis;
    }drop;
    volatile drop drops[DROPS_AMOUNT];
    /* Función para inicializar el Timer0 y generar */
    /* la temporización de 1 Sec. */
    void Timer0_Ini ( void );
    /* Función para verificar bandera del segundo */
    uint8_t Timer0_SecFlag ( void );

//Funciones para el timer 2
    uint32_t millis( void );
    void delay(uint16_t msWaitTime);
    void MiliTimerRegister(void (*callback)(), uint16_t sWaitTime);
    void SecTimerRegister(void (*callback)(), uint16_t sWaitTime);

#endif /* _TIMER0_H */