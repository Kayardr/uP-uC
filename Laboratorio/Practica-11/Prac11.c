#include "UART.h"
#include "Timer.h"
#include <avr/pgmspace.h>
const struct note ImperialMarch[] PROGMEM = {
	//for the sheet music see:
	//http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
	//this is just a translation of said sheet music to frequencies / time in ms
	//used TEMPO ms for a quart note
	{a, TEMPO},
	{a, TEMPO},
	{a, TEMPO},
	{f, TEMPO*3/4},
	{cH, TEMPO*1/4},

	{a, TEMPO},
	{f, TEMPO*3/4},
	{cH, TEMPO*1/4},
	{a, TEMPO*2},
	//first bit

	{eH, TEMPO},
	{eH, TEMPO},
	{eH, TEMPO},
	{fH, TEMPO*3/4},
	{cH, TEMPO*1/4},

	{gS, TEMPO},
	{f, TEMPO*3/4},
	{cH, TEMPO*1/4},
	{a, TEMPO*2},
	//second bit...

	{aH, TEMPO},
	{a, TEMPO*3/4},
	{a, TEMPO*1/4},
	{aH, TEMPO},
	{gSH, TEMPO/2},
	{gH, TEMPO/2},

	{fSH, TEMPO*1/4},
	{fH, TEMPO*1/4},
	{fSH, TEMPO/2},
	{0,TEMPO/2},
	{aS, TEMPO/2},
	{dSH, TEMPO},
	{dH, TEMPO/2},
	{cSH, TEMPO/2},
	//start of the interesting bit

	{cH, TEMPO*1/4},
	{b, TEMPO*1/4},
	{cH, TEMPO/2},
	{0,TEMPO/2},
	{f, TEMPO*1/4},
	{gS, TEMPO},
	{f, TEMPO*3/4},
	{a, TEMPO*1/4},

	{cH, TEMPO},
	{a, TEMPO*3/4},
	{cH, TEMPO*1/4},
	{eH, TEMPO*2},
	//more interesting stuff (this doesn't quite get it right somehow)

	{aH, TEMPO},
	{a, TEMPO*3/4},
	{a, TEMPO*1/4},
	{aH, TEMPO},
	{gSH, TEMPO/2},
	{gH, TEMPO/2},

	{fSH, TEMPO*1/4},
	{fH, TEMPO*1/4},
	{fSH, TEMPO/2},
	{0,TEMPO/2},
	{aS, TEMPO/2},
	{dSH, TEMPO},
	{dH, TEMPO/2},
	{cSH, TEMPO/2},
	//repeat... repeat

	{cH, TEMPO*1/4},
	{b, TEMPO*1/4},
	{cH, TEMPO/2},
	{0,TEMPO/2},
	{f, TEMPO/2},
	{gS, TEMPO},
	{f, TEMPO*3/4},
	{cH, TEMPO*1/4},

	{a, TEMPO},
	{f, TEMPO*3/4},
	{c, TEMPO*1/4},
	{a, TEMPO*2},
	//and we're done
	{END, TEMPO}
};
const struct note AngelesAzules[] PROGMEM ={
	{bL, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{b, TEMPO_500*5/4},

	{a, TEMPO_500*3/8},
	{gS, TEMPO_500*3/4},
	{fS, TEMPO_500*3/8},
	{d, TEMPO_500*3/4},
	{bL, TEMPO_500*3/2},
	//first bit

	{bL, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{b, TEMPO_500*5/4},

	{a, TEMPO_500*3/8},
	{gS, TEMPO_500*3/4},
	{fS, TEMPO_500*3/8},
	{d, TEMPO_500*3/4},
	{bL, TEMPO_500*3/2},
	//first bit

	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{cS, TEMPO_500*3/8},
	{d, TEMPO_500*5/8},
	{aL, TEMPO_500*5/4},
	
	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{cS, TEMPO_500*3/8},
	{d, TEMPO_500*5/8},
	{aL, TEMPO_500*5/8},

//****************

	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{e, TEMPO_500*3/8},
	{fS, TEMPO_500*5/8},
	{cS, TEMPO_500*5/4},

	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{e, TEMPO_500*3/8},
	{fS, TEMPO_500*5/8},
	{cS, TEMPO_500*5/8},

//*****************

	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{e, TEMPO_500*1/2},
	{d, TEMPO_500*1/2},
	{cS, TEMPO_500*3},

	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{e, TEMPO_500*1/2},
	{d, TEMPO_500*1/2},
	{cS, TEMPO_500*3},

//Se repite todo*****

	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{cS, TEMPO_500*3/8},
	{d, TEMPO_500*5/8},
	{aL, TEMPO_500*5/4},
	
	{d, TEMPO_500*3/8},
	{d, TEMPO_500*3/8},
	{cS, TEMPO_500*3/8},
	{d, TEMPO_500*5/8},
	{aL, TEMPO_500*5/8},

//****************

	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{e, TEMPO_500*3/8},
	{fS, TEMPO_500*5/8},
	{cS, TEMPO_500*5/4},

	{fS, TEMPO_500*3/8},
	{fS, TEMPO_500*3/8},
	{e, TEMPO_500*3/8},
	{fS, TEMPO_500*5/8},
	{cS, TEMPO_500*5/8},

//*****************

	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{e, TEMPO_500*1/2},
	{d, TEMPO_500*1/2},
	{cS, TEMPO_500*3},

	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*1/2},
	{e, TEMPO_500*1/2},
	{d, TEMPO_500*1/2},
	{cS, TEMPO_500*3},
	//and we're done
	{END, TEMPO}
};

const struct note SomethingJLT[] PROGMEM = {
	/*https://musescore.com/user/20426336/scores/3957616*/
	{d, TEMPO},
	{d, TEMPO*1/2},
	{c, TEMPO*1/2},
	{d, TEMPO},
	{d, TEMPO*1/2},
	{c, TEMPO*1/2},
	//2
	{d, TEMPO},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{c, TEMPO*1/2},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	//3
	{d, TEMPO},
	{d, TEMPO*1/2},
	{c, TEMPO*1/2},
	{d, TEMPO},
	{d, TEMPO*1/2},
	{c, TEMPO*1/2},
	//4
	{d, TEMPO*3/2},
	{d, TEMPO*1/4},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	//5
	{a, TEMPO*3/2},
	{d, TEMPO*1/4},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{e, TEMPO*1/2},
	{c, TEMPO*1/2},
	//6
	{d, TEMPO*3/2},
	{d, TEMPO*1/4},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	//7
	{aS, TEMPO*3/2},
	{d, TEMPO*1/4},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{e, TEMPO*1/2},
	{c, TEMPO*1/2},
	//8
	{d, TEMPO*3/2},
	{f, TEMPO*1/4},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	//9
	{g, TEMPO*3/2},
	{g, TEMPO*1/4},
	{g, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{f, TEMPO*1/2},
	//10
	{f, TEMPO*2},
	{0, TEMPO/2},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{f, TEMPO*1/2},
	//11
	{f, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{d, TEMPO*1/2},
	//12
	{d, TEMPO},
	{d, TEMPO*1/2},
	{d, TEMPO*1/2},
	{f, TEMPO*1/2},
	{a, TEMPO*1/2},
	{a, TEMPO*1/2},
	{a, TEMPO*1/2},
	//13
	{b, TEMPO*3/2},
	{b, TEMPO*1/4},
	{b, TEMPO*1/2},
	{a, TEMPO*1/2},
	{a, TEMPO*1/2},
	{g, TEMPO*1/2},
	//14
	{f, TEMPO},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{a, TEMPO*1/2},
	//15
	{a, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{g, TEMPO*1/2},
	//16
	{f, TEMPO*3/2},
	{d, TEMPO*1/4},
	{f, TEMPO*1/2},
	{a, TEMPO*1/2},
	{a, TEMPO*1/2},
	{a, TEMPO*1/2},
	//17
	{b, TEMPO*3/2},
	{b, TEMPO*1/4},
	{b, TEMPO*1/4},
	{a, TEMPO*1/2},
	{a, TEMPO*1/2},
	{g, TEMPO*1/2},
	//18
	{f, TEMPO*3/4},
	{f, TEMPO*1/4},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	//19
	{g, TEMPO*3/8},
	{e, TEMPO*5/8},
	{e, TEMPO*1/4},
	{e, TEMPO*1/4},
	{e, TEMPO*1/4},
	{g, TEMPO*1/4},
	{f, TEMPO*1/4},
	//20
	{f, TEMPO},
	{d, TEMPO*1/2},
	{f, TEMPO*1/2},
	{f, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	{e, TEMPO*1/2},
	//21
	{e, TEMPO*1/4},
	{d, TEMPO},
	{d, TEMPO*1/4},
	{e, TEMPO*1/4},
	{f, TEMPO*1/4},
	{d, TEMPO*1/4},
	{e, TEMPO*1/4},
	{f, TEMPO*1/4},
	{END, TEMPO}
};
PGM_P songs[] = {
	(PGM_P)ImperialMarch,
	(PGM_P)SomethingJLT,
	(PGM_P)AngelesAzules
};

int main(void)
{
	UART_Init(0, 250000,8, 1, 2, 0);
	//UART_AutoBaudRate();
	InitPorts();
	Timer0_Ini();
    UART0_puts("No ha iniciado la cancion");
	char str[5];
	uint8_t i = 1;
	uint8_t max = sizeof(songs)/sizeof(PGM_P);
	while(1){
		if (UART_avalaible()){ 
			switch (UART0_getchar()){//Devolver esto a la normalidad
			case 'p':
			case 'P': // Play Song
					UART0_puts("Ha iniciado la cancion");
					Timer2_Play(songs[i],sizeof(ImperialMarch)/sizeof(struct note));
					break;
			case 'V': //Increase Volume
					Timer2_Volume(1);
					break;
			case 'v'://Decrease Volume
					Timer2_Volume(0);
					break;
          
      		case 'n':
      		case 'N': //Next song
			  		i++;
					i %= max;
					Timer2_Play(songs[i], 0);
					break;
			case 'b':
      		case 'B'://Previous song
			  		if(i==0)
					  i = max-1;
					else
						i--;
					break;
			
      default:
					break;
			
			}
		}
		gotoxy(0,0);
		UART0_itoa(str, volume, 10);
		UART0_puts(str);
	}
	return 0;
}