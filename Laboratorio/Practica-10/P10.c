#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "Timer0.h"
#include "Timer2.h"

//DEFINICIONES PARA CADENAS
#define TX_LONG_MIN   8       //Longitud minima de la cadena
#define TX_LONG_MAX   20      //Longitud maxima de la cadena
#define COLUMNS       268      //Cantidad de columnas
#define ROWS          56      //Cantidad de renglones

#define CONSTANTE     12

uint8_t sec;
uint8_t min;
uint8_t hrs;
char timer_g[10];
enum DropStates{
  dead = 0,
  alive,
  dripping,
  deading
};
//Structures

//Externs

//Funciones protoripo
void genDropPos(drop *data, uint8_t seed);
void genDropText(drop* data, uint8_t size, uint8_t seed);
void reduceDropText(drop* data);
void printDrop(drop* data);
void killDrop(drop* data);
uint8_t corruptData(drop* data);
uint16_t myRand(uint8_t seed, uint8_t c, uint8_t a);


int main(void){
    uint16_t i, j;
    sei();
    UART_Init(0, 1000000, 8, 3, 1, 1); // <--- MODIFICAR AQUI
    clrscr();
    UART0_puts("\033[?25l");
    //Inicializar tiempo de las gotas
    
    i=0;
    Timer2_Ini();
    Timer0_Ini();
    while(1){
      if(drops[i].state == dead){
        genDropPos(&drops[i], millis()*i);
        drops[i].millis = myRand(millis(), CONSTANTE, millis()/3);
        drops[i].state = alive;
        for(j = 0; j<DROPS_AMOUNT; j++){
            if(drops[i].x_pos == drops[j].x_pos && i!=j){
              drops[i].state = dead;
              break;
            }
        }
      }
      if(drops[i].millis == 0){
        killDrop(&drops[i]);
        printDrop(&drops[i]);
        reduceDropText(&drops[i]);
        drops[i].millis = myRand(millis(), CONSTANTE, millis()/3);
      }
      i++;
      i%= DROPS_AMOUNT;
      draw_Timer();
    }
    return 0;
}

void draw_Timer(){

  if(Timer2_SecFlag()){
    gotoxy(COLUMNS-10, 0);
    UART0_puts("00:00:00");
    sec++;

    if(sec == 60){
      min++;
      
      if(min == 60)
        hrs++;
        min %= 60;
    }
    sec %= 60;
    /*Horas*/
    UART0_itoa(timer_g, hrs, 10);
      if(hrs>9)
        gotoxy(COLUMNS-7, 0);
      else
        gotoxy(COLUMNS-6, 0);
    UART0_puts(timer_g);
    /*Minutos*/
    UART0_itoa(timer_g, min, 10);
      if(min>9)
        gotoxy(COLUMNS-7, 0);
      else
        gotoxy(COLUMNS-6, 0);
    UART0_puts(timer_g);
    /*Segundos*/
    UART0_itoa(timer_g, sec, 10);
    if(sec>9)
      gotoxy(COLUMNS-4, 0);
    else
      gotoxy(COLUMNS-3, 0);
    UART0_puts(timer_g);
  }
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
    UART_putchar(genText(millis()*data->x_pos+data->y_pos));
  }
  if(data->state != dead && data->y_pos < ROWS){
    setColor(YELLOW);
    gotoxy(data->x_pos, data->y_pos);
    UART_putchar(genText(millis()*data->x_pos+2));
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
  if((myRand(millis(), CONSTANTE, millis()*2)%100) >60){
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

/*
void quickSort(drop *data, uint8_t low, uint8_t high){
  uint8_t i;
  if(low <high){
    i = partition(data, low, high);
    quickSort(data, low, i-1);
    quickSort(data, i+1, high);
  }
}

void partition(drop *data, uint8_t low, uint8_t high){
  drop pivot = data[high];
  drop aux;
  uint8_t i = (low - 1);
  uint8_t j;
  for(j = 0; j < high-1; j++){
    if(data[j].millis < pivot.millis){
      i++;
      aux = data[i];
      data[i] = data[j];
      data[j] = aux;
    }
  }
  aux = data[i+1];
  data[hight] = data[i+1];
  data[i+1] = aux;
}*/