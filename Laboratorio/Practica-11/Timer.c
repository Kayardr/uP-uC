#include <avr/interrupt.h>
#include <avr/io.h>
#include "Timer.h"
#include "UART.h"
#define P 1024
#define TICKS(f) 16E6/P/f

static volatile uint32_t ms;			//Contador de milisegundos
static volatile uint8_t secF;			//Bandera de segundos
volatile uint8_t volume;
volatile struct note* song_ptr;
volatile uint16_t n_note;				//Indice de la nota actual
volatile uint16_t m_note;				//Maximo rango de notas

volatile uint16_t ms_delay;				//Contador de tiempo de notas/silencios
volatile uint8_t new_note_f;			//Bandera de cabio de nota
volatile uint16_t current_delay;		//Variable que TOPE para un delay

void Timer0_Ini ( void ){
	/* 	Permanece igual, ocasionando una interrupción 
		cada 1 ms en modo CTC. */
	TCCR0A |= (1 << WGM01);					/*Inicializar Timer en modo CTC*/
	TCCR0B |= (0b011 << CS00);				/*Establecer el preescalador a 64*/
	TCNT0 = 0;								/*Establecer el contador en 0*/
	OCR0A = TOP_V(CLOCKA, 64, 1);			/*Establecer el valor de comparacion*/
	TIMSK0 |= (1 << OCIE0A);				/*Se habilitan las interrupciones por comparacion*/
	sei();									/*Habilita las interrupciones globales*/
}

ISR(TIMER0_COMPA_vect){ 
	ms++;
	ms_delay++;
	/* 	Código para actualizar bandera de segundos */
	if(!(ms%1000))
		secF = 1;
	/*	Agregar las instrucciones necesarias para reproducir
		la siguiente nota en el arreglo dependiendo de la duración, 
		e insertar los silencios entre cada nota. */
	
	/*Comprobar si los ms de la Nota han alcanzado el umbral de cambio*/
	
	if(ms_delay >= current_delay){
		/**/
		ClrBitPort(PORTF, 0);
		ms_delay = 0;		//Se establece el contador de tiempo de delay a 0
		/*Comprobar si el silencio entre notas ha terminado*/
		if(new_note_f){		//Si ya ha terminado entonces cargar la nueva nota
			/*Generar la frecuencia de la nota*/
			
			Timer2_Freq_Gen(TICKS(song_ptr[n_note].freq));
			current_delay = song_ptr[n_note].delay;		//Se establece el nuveo delay de la nota
			new_note_f = 0;		//La bandera de nueva nota es desactivada
			n_note++; 			//Se incrementa el indice de la nota
		}else{				//Si hay silencio entonces...
			
			new_note_f = 1;		//Activar la bandera de nueva nota
			current_delay = SILENCE;	//Indicar que hay un delay de 10 ms entre notas
			Timer2_Freq_Gen(0);			//Se manda silencio
			SetBitPort(PORTF, 0);
		}
	}
	
}

void Timer2_Freq_Gen(uint8_t ticks){
	/* 	Si "ticks" es mayor que 0 entonces, inicializa y habilita el Generador 
		de Frecuencia del Timer2 con el tope dado por "ticks".
		De lo contrario se requiere deshabilitar el Generador, generando de 
		esta forma el silencio (0 lógico). */
	if(ticks && (volume > 0)){
		/*Deshabilitar interrupciones*/
		/*Nuevos valores de TCNT2 y TCCR2A, TCCR2B(Modo de operacion)*/
		TCNT2 = 0;
		TCCR2A |= (1 << COM2B1) | (0b11 << WGM20);
		TCCR2B |= (1 << WGM22) | (0b111 << CS20);
		/*Asignar #_Ticks en OCR2A*/
		OCR2A = ticks - 1;
		/*Asignar frecuencia a OCR2B*/
		OCR2B = PWM_freq(OCR2A, volume, PRESCALER);
	}else
		TCCR2B = 0;
}

void Timer2_Play(const struct note song[], unsigned int len){
	/*	Función que establece las condiciones necesarias para que
		el generador recorra el arreglo de notas. */
	song_ptr = song;
	
	n_note = 0;
	current_delay = song_ptr[n_note].delay;
	m_note = len;
	volume = 128;
	DDRH |= (1 << DDH6);
}

void Timer2_Volume(uint8_t direction){
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
