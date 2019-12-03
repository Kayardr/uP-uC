/*
Programa que determina la amplitud de la señal de entrada al ADC segun el siguiente diagrama
Castañon Renteria Ricardo
Microprocesadores y Microcontroladores
*/
#define RANGE 15
ASC_init(){
    ADMUX |= (1 << ADLAR);
    ADCSRB = 0;
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADPS2);
}

uint8_t ADC_readAmp(){
    uint8_t i;
    uint16_t r;
    ADCSRA |= (1 << ADSC);
    for(i = 0; i < 8; i++){
        ADCSRA |= (1 << ADSC);
        while(ADCSRA & (1 << ADSC));
        if(ADCH > RANGE)
            r+=ADCH;
    }
    return (uint8_t)(r / 8);
}