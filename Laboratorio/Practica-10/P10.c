#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

//DEFINICIONES PARA CADENAS
#define TX_LONG_MIN 8
#define TX_LONG_MAX 16
#define LINES   50

//COLORS
#define BASE_C 2
#define DIRE_C 5

//Structures
struct 
{
  char str[TX_LONG_MAX];
  uint8_t x_pos;
  uint8_t y_pos;
}drop;


int main(void){
    sei();
    UART_Init(0, 12345, 8, 1, 2); // <--- MODIFICAR AQUI
    while(1){
      //En un lapso de tiempo
        //Generar una cadena en una posicion x, y aleatoria, siempre y cuando no haya otra cadena ya
      
      //Hay espacio para generar una nueva cadena


      //Escribe n-1 caracteres de la cadena en tono verde, y el caracter n en tono amarillo
        //X no variara pero y cambiara
        //Esto se debera hacer para todas las cadenas existentes
      
      //Delay?

      //Clear

    }
    return 0;
}

void genDropText(drop &data, uint8_t size){
  uint8_t i;
  for(i = 0; i < size; i++){
    data->str[i] = (myRand(millis) % 222) + '!'; //LLENAR ESTA PARTE
    //<<++++==== TODO
  }
}

void printDrop(drop &data){
  int index = 0;
  setColor(YELLOW);                       //Establece el color de la gota en amarillo
  while(*str != '\0'){  
    gotoxy(data->x_pos, data->y_pos-index); //Actualiza la posicion de Y, x deberia permanecer en todo momento
    UART_putchar(*str);                   //Escribe el caracter
    setColor(GREEN);                      //Establece el color en verde para el resto de la gota
    index++;                              //Decrementa la posicion de la gota, salvo el punto amarillo
    *str++;                               //No creo que haga falta comentar
  }
  data->y_pos++;                         //Incrementa la posicion de y
}