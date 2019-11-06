#include <avr/io.h>

// Macros
#define SetBitPort(port, bit) __asm__ ( "sbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit) )
#define ClrBitPort(port, bit) __asm__ ( "cbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit) )

// Externs

extern uint8_t myRand(uint8_t seed);

#define TIME_WINDOW 30
#define SEED 10

enum ButtonStates{
  eBtnUndefined = 0,
  eBtnShortPressed,
  eBtnLongPressed
};

enum GameStates{
  eGameRestart = 0,
  eWaitForStart,
  eStartCount,
  eEndCount,
  eGameOver,
  eYouWin,
  eYouLoose
};

// Prototypes
void delay(uint16_t mseg){
	mseg = mseg * 840;
	while(mseg--);
}
void InitPorts(void){
	DDRF  = 0b01111111;
  PORTF = 0b10111111;
}

uint8_t checkBtn(void);
void updateLeds(uint8_t gameState);
void leeds(uint8_t c);

// Global variable
uint32_t last;
uint32_t millis;
uint8_t count;

int main(void){
  uint8_t  currentGameState = eGameRestart;
  uint16_t countdown = 0;
  uint16_t countup = 0;
  last = millis;
	InitPorts();
	delay(1);
	while(1){
		
    switch(checkBtn()){
			case eBtnShortPressed: currentGameState++;
          break;
			case eBtnLongPressed:	currentGameState = eGameRestart;
          break;
		}
    
    switch(currentGameState){
      case eGameRestart:
          countdown = (myRand(SEED)+1)*20 % 255;
          count = 0;
          countup = 0;
          currentGameState++;
          break;
      case eWaitForStart:
          break;
      case eStartCount:
          if(!(millis % 10)){
            countdown--;
            count = countdown;
          }
          if (countdown == 0){
            currentGameState++;
            countup = 0;
          }
          break;
      case eEndCount:
          if (countdown != 0)
            currentGameState++;
          else{
            countup++;
          }
          break;
      case eGameOver:
          if ((countdown+countup)>TIME_WINDOW){
            currentGameState = eYouLoose;
            count = 0b11110000;
          }
          else {
            currentGameState = eYouWin;
            count = 0b11111111;
          }
          break;
    }
    if(countup < 300)
      SetBitPort(PORTF, 5);
    else
      ClrBitPort(PORTF, 5);

		updateLeds(currentGameState);
		delay(1);
		millis++;	
	}
}

uint8_t checkBtn(void){    
    uint8_t status = eBtnUndefined;
    if((millis-last)==0 || (millis-last)>5){
      if((PINF & 0b10000000)){
        if(millis-last < 100 && millis-last>0)
          status = eBtnShortPressed;
        else if(millis-last>=100)
          status = eBtnLongPressed;
        last = millis+1;
      }
    }
    return status;
}

void updateLeds(uint8_t gameState){
  switch(gameState){
    case eWaitForStart:
      leeds(~count);
      if(!(millis % 10)){
        if(count==0)
          count = 0b10000000;
        else
          count = count >> 1;
      }   
      break;
    case eStartCount:
      leeds(count);
      break;
    case eEndCount:
      leeds(0);
      break;
    case eYouLoose:
      leeds(count);
      if(!(millis % 50))
        count = ~count;
      break;
    case eYouWin: 
      leeds(count);
      if(!(millis % 25))
        count = ~count;
      break;
  }
}

void leeds(uint8_t c){
  
  SetBitPort(DDRF, 0);
  SetBitPort(DDRF, 1);
  ClrBitPort(DDRF, 2);
  ClrBitPort(DDRF, 3);
  
  //LED 1
  ClrBitPort(PORTF, 0);
  if((1 & c))         SetBitPort(PORTF, 1);
  else                      ClrBitPort(PORTF, 1);
  delay(1);
  //LED 2
  ClrBitPort(PORTF, 1);
  if((1 & (c >> 1)))  SetBitPort(PORTF, 0);
  else                      ClrBitPort(PORTF, 0);
  delay(1);
  //LED 3
  ClrBitPort(DDRF, 0);
  SetBitPort(DDRF, 2);
  ClrBitPort(PORTF, 1);
  if(1 & (c >> 2))   SetBitPort(PORTF, 2);
  else                     ClrBitPort(PORTF, 2);
  delay(1);

  //LED 4
  ClrBitPort(PORTF, 2);
  if(1 & (c >> 3))   SetBitPort(PORTF, 1);
  else                     ClrBitPort(PORTF, 1);
  delay(1);

  //LED 5
  ClrBitPort(DDRF, 1);
  SetBitPort(DDRF, 0);
  ClrBitPort(PORTF, 2);
  if(1 & (c >> 4))   SetBitPort(PORTF, 0);
  else                     ClrBitPort(PORTF, 0);
  delay(1);

  //LED 6
  ClrBitPort(PORTF, 0);
  if(1 & (c >> 5))   SetBitPort(PORTF, 2);
  else                     ClrBitPort(PORTF, 2);
  delay(1);

  //LED 7
  SetBitPort(DDRF, 3);
  ClrBitPort(DDRF, 2);
  ClrBitPort(PORTF, 0);
  if(1 & (c >> 6))   SetBitPort(PORTF, 3);
  else                     ClrBitPort(PORTF, 3);
  delay(1);

  //LED 8
  ClrBitPort(PORTF, 3);
  if(1 & (c >> 7))   SetBitPort(PORTF, 0);
  else                     ClrBitPort(PORTF, 0);
  delay(1);
  
}
