#include <avr/interrupt.h>
#include <avr/io.h>
#include "Timer.h"
#define P 1024
#define TICKS(f) 16E6/P/f

static volatile uint32_t ms;
static volatile uint8_t secF;
volatile uint8_t volume;
volatile struct note* song_ptr;
volatile uint16_t n_nota;
volatile uint16_t m_nota;
volatile uint8_t delay_f;

void Timer0_Ini ( void ){
	/* 	Permanece igual, ocasionando una interrupción 
		cada 1 ms en modo CTC. */
	TCCR0A |= (1 << WGM01);					/*Inicializar Timer en modo CTC*/
	TCCR0B |= (0b011 << CS00);				/*Establecer el preescalador a 64*/
	TCNT0 = 0;								/*Establecer el contador en 0*/
	OCR0A = TOP_V(CLOCKA, 64, 1);			/*Establecer el valor de comparacion*/
	TIMSK0 = (1 << OCIE0A);					/*Se habilitan las interrupciones por sobreflujo*/
	sei();
}

ISR(TIMER0_COMPA_vect){ 
	ms++;
	/* 	Código para actualizar bandera de segundos */
	if(!(ms%1000))
		secF = 1;
	/*	Agregar las instrucciones necesarias para reproducir
		la siguiente nota en el arreglo dependiendo de la duración, 
		e insertar los silencios entre cada nota. */
	if((ms % song_ptr[n_nota].delay) && delay_f == 1){
		if(song_ptr[n_nota].freq > 1)
			Timer2_Freq_Gen(TICKS(song_ptr[n_nota].freq));
		else
			Timer2_Freq_Gen(0);
		n_nota++;
		delay_f = 0;
	}else{
		delay_f = 1;
		Timer2_Freq_Gen(0);
	}
	
}

void Timer2_Freq_Gen(uint8_t ticks){
	/* 	Si "ticks" es mayor que 0 entonces, inicializa y habilita el Generador 
		de Frecuencia del Timer2 con el tope dado por "ticks".
		De lo contrario se requiere deshabilitar el Generador, generando de 
		esta forma el silencio (0 lógico). */
	if(ticks && (volume > 0)){
		/*Deshabilitar interrupciones*/
		TIMSK2 = 0;
		/*Seleccion del reloj fuente*/
		ASSR &= (0 << AS2);
		/*Nuevos valores de TCNT2 y TCCR2A, TCCR2B(Modo de operacion)*/
		TCNT2 = 0;
		TCCR2A |= (0b11 << WGM20);
		TCCR2B |= (0b1 << WGM22) | (0b111 << CS20);
		/*Asignar #_Ticks en OCR2A*/
		OCR2A = ticks - 1;
		/*Asignar frecuencia a OCR2B*/
		OCR2B = PWM_freq(OCR2A, volume, PRESCALER);
	}else
		OCR2B = 0;
}

void Timer2_Play(const struct note song[], unsigned int len){
	/*	Función que establece las condiciones necesarias para que
		el generador recorra el arreglo de notas. */
	song_ptr = song;
	n_nota = 0;
	m_nota = len;
	volume = 64;
	DDRH |= (1 << DDH6);
}

void Timer2_Volume(int8_t direction){
	/* 	Ajusta el ciclo de trabajo para incrementar o decrementar  el volumen
	   	de las notas que se estan generando. */
	if(direction == 1){
		volume++;
		volume %= 128;
	}else if(direction == -1){
		if(volume>0)
			volume--;
		else
			volume = 128;
	}
}
