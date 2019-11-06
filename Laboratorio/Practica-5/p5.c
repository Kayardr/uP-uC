extern void putchar( char dato );
extern unsigned char getchar( void );
void puts ( char *str );
void printBin(unsigned char number);


#define BYTE unsigned char
#define WORD unsigned int
#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43
#define PTOs_all_out 0x80
#define OpCode 0x89

extern void outportb(WORD port, BYTE dato);
extern BYTE inportb(WORD port);

void SetBitPort(WORD Puerto, BYTE num_bit);
void ClrBitPort(WORD Puerto, BYTE num_bit);
void NotBitPort(WORD Puerto, BYTE num_bit);
BYTE TestBitPort(WORD Puerto, BYTE num_bit);
void Delay(int ms);
void PrintLeds(BYTE dato);

BYTE dato;
BYTE i;

void main( void ){
	puts("Practica 5\n\r"); /* imprimir mensaje */
	outportb(RCtr, 0x88); /* inicializar 8255 */
	for(i = 0; i < 8; i++){
		putchar(i+'0');
		getchar();
		putchar(TestBitPort(PC, 4)+'0');
		dato |= TestBitPort(PC, 4) << i;
		puts("\n\r");
	}
	printBin(dato);
	outportb(RCtr, PTOs_all_out);
	
	while(1){
		PrintLeds(dato);
	}
}

void SetBitPort(WORD Puerto, BYTE num_bit){
	outportb( Puerto , inportb( Puerto )|( 0x01 << num_bit ) );
}

void ClrBitPort(WORD Puerto, BYTE num_bit){
	outportb( Puerto , inportb( Puerto )&(~(0x01 << num_bit)));
}

void NotBitPort(WORD Puerto, BYTE num_bit){
	outportb( Puerto , inportb( Puerto )^( 0x01 << num_bit ) );
}

BYTE TestBitPort(WORD Puerto, BYTE num_bit){
	if((inportb(Puerto) & (0x01 << num_bit))!=0)
		return 1;
	return 0;
}

void PrintLeds(BYTE dato){
	outportb(RCtr, OpCode); 		/*	PA: S 	PB: S	PC:	E*/

	ClrBitPort(PA, 0);	/*PA = S 0, PB = S x, PC = E 1*/
	(0x1 & dato) ? SetBitPort(PB, 0) : ClrBitPort(PB, 0);
	Delay(10);

	ClrBitPort(PB, 0);	/*PA = S x, PB = S 0, PC = E 1*/
	(0x1 & (dato>>1)) ? SetBitPort(PA, 0) : ClrBitPort(PA, 0);
	Delay(10);

	ClrBitPort(PB, 0);				/*PA = E 1, PB = S 0, PC = S x*/
	NotBitPort(RCtr, 4);			/*	PA: E 	PB: S	PC:	E*/
	NotBitPort(RCtr, 0);			/*	PA: E 	PB: S	PC:	S*/
	(0x1 & (dato>>2)) ? SetBitPort(PC, 0) : ClrBitPort(PC, 0);
	Delay(10);

	ClrBitPort(PC, 0);
	(0x1 & (dato>>3)) ? SetBitPort(PB, 0) : ClrBitPort(PB, 0);
	Delay(10);

	ClrBitPort(PC, 0);
	NotBitPort(RCtr, 4);			/*	PA: S 	PB: S	PC:	S*/
	NotBitPort(RCtr, 1);			/*	PA: S 	PB: E	PC:	S*/
	(0x1 & (dato>>4)) ? SetBitPort(PA, 0) : ClrBitPort(PA, 0);
	Delay(10);

	ClrBitPort(PA, 0);
	(0x1 & (dato>>5)) ? SetBitPort(PC, 0) : ClrBitPort(PC, 0);
	Delay(10);
}

void Delay(int ms){
	int i = 0;
	while(i++ < ms);
}

void puts ( char *str ){
	while( *str )
		putchar( *str++ );
}

void printBin(unsigned char number){
	int aux = 0x80;
	do{
		if((aux & number)!= 0)
			putchar('1');
		else
			putchar('0');
		aux >>= 1;
	}while(aux!=0);
}

