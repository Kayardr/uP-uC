#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

//DEFINICIONES PARA CADENAS
#define TX_LONG_MIN   8       //Longitud minima de la cadena
#define TX_LONG_MAX   20      //Longitud maxima de la cadena
#define COLUMNS       268      //Cantidad de columnas
#define ROWS          56      //Cantidad de renglones
#define DROPS_AMOUNT  300       //Cantidad de gotas a mostrar
#define CONSTANTE     12

enum DropStates{
  dead = 0,
  alive,
  dripping,
  deading
};
//Structures
typedef struct drop_s{
  uint16_t x_pos;
  uint8_t y_pos;
  uint8_t size;
  uint8_t state;
}drop;
//Externs

//Funciones protoripo
void genDropPos(drop *data, uint8_t seed);
void genDropText(drop* data, uint8_t size, uint8_t seed);
void reduceDropText(drop* data);
void printDrop(drop* data);
void killDrop(drop* data);
uint8_t corruptData(drop* data);

uint16_t myRand(uint8_t seed, uint8_t c, uint8_t a);

//Globales
uint32_t millis;

int main(void){
    drop drops[DROPS_AMOUNT];
    uint16_t i, j;
    sei();
    UART_Init(0, 1000000, 8, 3, 1, 1); // <--- MODIFICAR AQUI
    clrscr();
    UART0_puts("\033[?25l");
    for(i = 0; i < DROPS_AMOUNT; i++)
      drops[i].state = dead;
    while(1){
      if(drops[i].state ==  dead){
        genDropPos(&drops[i], millis*i);
        drops[i].state = alive;
        for(j = 0; j<DROPS_AMOUNT; j++){
          if(drops[i].x_pos == drops[j].x_pos && i!=j){
            drops[i].state = dead;
            break;
          }
        }
      }else{
        killDrop(&drops[i]);
        if(!corruptData(&drops[i])){
          printDrop(&drops[i]);
          reduceDropText(&drops[i]);
        }
        
      }
      i++;
      i %= DROPS_AMOUNT;
      millis++;
      

    }
    return 0;
}



void genDropPos(drop *data, uint8_t seed){
  data->size = ((myRand(seed, CONSTANTE, seed*2))%(TX_LONG_MAX-TX_LONG_MIN))+TX_LONG_MIN;
  data->x_pos = (myRand(seed/6, CONSTANTE, seed/3)*20) % (COLUMNS-1);
  data->y_pos = myRand(seed/3, CONSTANTE, seed/4) % (ROWS/2);
}

char genText(uint8_t seed){
  return (myRand(seed*4, CONSTANTE, seed/4) % 94) + 0x21; //LLENAR ESTA PARTE
}

void reduceDropText(drop *data){
  if(data->y_pos == ROWS){
    data->y_pos--;
    data->size--;
    if(data->size < 2)
      data->state = deading;
  }
}

void printDrop(drop *data){
  if(data->y_pos - (data->size+1) > 0){
    gotoxy(data->x_pos, data->y_pos - (data->size+1));
    UART_putchar(' ');
  }
  
  if(data->state == dripping && data->state != deading && (data->y_pos-1) != 0){
    setColor(GREEN);
    gotoxy(data->x_pos, data->y_pos-1);
    UART_putchar(genText(millis*data->x_pos+data->y_pos));
  }
  if(data->state != dead && data->y_pos < ROWS){
    setColor(YELLOW);
    gotoxy(data->x_pos, data->y_pos);
    UART_putchar(genText(millis*data->x_pos+2));
  }
  else{
    gotoxy(data->x_pos, data->y_pos);
    UART_putchar(' ');
  }
  
  if(data->state == alive)
    data->state = dripping;
  data->y_pos++;                            
}

uint8_t corruptData(drop* data){
  if((myRand(millis, CONSTANTE, millis*2)%100) >60){
    printDrop(data);
    data->y_pos--;
    return 1;
  }
  return 0;
}

void killDrop(drop* data){
  if((data->y_pos - data->size)+1 == ROWS)
    data->state = dead;
}

uint16_t myRand(uint8_t seed, uint8_t c, uint8_t a){
  return (((uint16_t)seed*(uint16_t)a)+(uint16_t)c);
}