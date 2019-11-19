#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

//DEFINICIONES PARA CADENAS
#define TX_LONG_MIN   8       //Longitud minima de la cadena
#define TX_LONG_MAX   16      //Longitud maxima de la cadena
#define COLUMNS       315      //Cantidad de columnas
#define ROWS          68      //Cantidad de renglones
#define DROPS_AMOUNT  80       //Cantidad de gotas a mostrar
#define REFRESH_RATE  100
#define CONSTANTE     12

//Structures
typedef struct drop_s{
  char str[TX_LONG_MAX];
  uint8_t x_pos;
  uint8_t y_pos;
  uint8_t size;
  uint8_t live;
}drop;
//Externs

//Funciones protoripo
void genDropPos(drop *data, uint8_t seed);
void genDropText(drop* data, uint8_t size, uint8_t seed);
void reduceDropText(drop* data);
void printDrop(drop* data);
void delay(uint16_t mseg);
uint16_t myRand(uint8_t seed, uint8_t c, uint8_t a);

//Globales
uint32_t millis;
uint32_t last;


int main(void){
    drop drops[DROPS_AMOUNT];
    uint8_t i, j;
    sei();
    UART_Init(0, 250000, 8, 3, 1, 1); // <--- MODIFICAR AQUI
    clrscr();
    for(i = 0; i < DROPS_AMOUNT; i++)
      drops[i].live = 0;
    last = millis;
    while(1){
      //Clear
      //clrscr();
      for(i = 0; i< DROPS_AMOUNT; i++){

        if(drops[i].live == 0){
          drops[i].live = 1;
          for(j = 0; j< i; j++){
            if(drops[i].x_pos == drops[j].x_pos){
              drops[i].live = 0;
              break;
            }
          }
          if(drops[i].live == 1){
            genDropPos(&(drops[i]), (uint8_t)millis+(i*2));
            genDropText(&(drops[i]), 8, (uint8_t)millis+(i*5));
            drops[i].live = 2;
          }
        }
        
        
        if(drops[i].live == 2){
          reduceDropText(&(drops[i]));
          printDrop(&(drops[i]));
          if((drops[i].y_pos-drops[i].size) == ROWS){
            drops[i].live = 0;
          }
        }
      }
      
      
      //Delay?
      //delay(1);
      millis++;
    }
    return 0;
}



void genDropPos(drop *data, uint8_t seed){
  data->x_pos = (myRand(seed/6, CONSTANTE, seed/3)*20) % COLUMNS;
  data->y_pos = myRand(seed/3, CONSTANTE, seed/4) % (ROWS/2);
}


void genDropText(drop *data, uint8_t size, uint8_t seed){
  uint8_t i;
  for(i = 0; i < size-1; i++){
    data->str[i] = (myRand(seed+i*4, CONSTANTE, seed/4) % 94) + 0x21; //LLENAR ESTA PARTE
    //<<++++==== TODO
  }
  data->size = size;
  data->str[size-1] = '\0';
}

void reduceDropText(drop *data){
  if(data->y_pos == ROWS){
    //data->y_pos--;
    data->size--;
    data->str[data->size] = '\0';
  }
}

void printDrop(drop *data){
  int index = 0;
  gotoxy(data->x_pos, data->y_pos - (data->size+1));
  UART_putchar(' ');
  while(data->str[index] != '\0'){  
    if(data->str[index+1] != '\0')
      setColor(GREEN);                                        //Establece el cuerpo de la gota en verde
    else  
       setColor(YELLOW);                                      //Establece el final de la gota en amarillo
    gotoxy(data->x_pos, (data->y_pos - (data->size-index)));   //Actualiza la posicion de Y, x deberia permanecer en todo momento
    UART_putchar(data->str[index]);                           //Escribe el caracter
    index++;                                        //Decrementa la posicion de la gota, salvo el punto amarillo                                         //No creo que haga falta comentar
  }
  data->y_pos++;                                    //Incrementa la posicion de y
}

void delay(uint16_t mseg){
	mseg = mseg * 840;
	while(mseg--);
}

uint16_t myRand(uint8_t seed, uint8_t c, uint8_t a){
  uint8_t i;
  for (i = 0; i < seed/2; i++){
    seed = a*seed+c;
  }
  return ((seed*a)+c);
}