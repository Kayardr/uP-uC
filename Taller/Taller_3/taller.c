void DisplayData(BYTE n);
int read(BYTE *port);

#define PA				0x40		/*Se pretende usar como salida (A)*/
#define PB				0x41		/*Se pretende usar como salida (B)*/
#define PC				0x42		/*Se pretende usar como entrada*/
#define CtlReg8255		0x43		/*Direccion para escribir palabras de control*/
/*Byte de control para el modo 0:
		 Binario		 HEX
		010001001		0x89h
*/
#define CB				0x89

#define BYTE unsigned char
#define WORD unsigned int
/*
Tabla para display de 7 segmentos (catodo comun)
Numero		abcdefgh		Valor HEX
===============================================
  0			11111100		   FCh
  1			01100000		   60h
  2			11011010		   DAh
  3			11110010		   F2h
  4			01100110		   66h
  5			10110110		   B6h
  6			10111110		   BEh
  7			11100000		   E0h
  8			11111110		   FEh
  9			11100110		   E6h
*/

int main(void){
	BYTE n = 0;
	BYTE port = 3;
	outportb(CtlReg8255, CB);
	while(1){
		n += read(&port);
		DisplayData(n);
		delay(200);
	}
	return 0;
}

void DisplayData(BYTE n){
	static BYTE DisplayA[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};
	static BYTE DisplayB[10] = {0, ~0x60, ~0xDA, ~0xF2, ~0x66, ~0xB6, ~0xBE, ~0xE0, ~0xFE, ~0xE6};
	n %=10;
	outportb(PA,DisplayA[n]);
	n %=10;
	outportb(PA,DisplayB[n]);
}

int read(BYTE *port){
	if(*port == 3)
		*port = inportb(PC);
	else{
		if(*port == 1){
			*port = inport(PC);
			if(*port == 3)
				return 1;
		}
		if(*port == 2){
			*port = inport(PC);
			if(*port == 3)
				return -1;
		}
	}
	return 0;
}

