extern unsigned char peek(unsigned int segment, unsigned int offset);
extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
extern void putchar( char dato );
extern unsigned char getchar( void );
void puts ( char *str );

/*
Test
*/
void dataBusTest(unsigned int segment, unsigned int offset);
void addressBusTest(unsigned int segment, unsigned int offset, unsigned int nBits);
void printBin(unsigned char number);

void main(){
	unsigned char a;
	unsigned char b;
	a = getchar();
	poke(200, 200, a);
	b = peek(200, 200);
	putchar(b);
	getchar();
	dataBusTest(0x200, 0x200);
	addressBusTest(0x200, 0x200, 0x7FF);
	getchar();
}

void puts ( char *str ){
	while( *str )
		putchar( *str++ );
}

/*Test para el bus de datos*/
void dataBusTest(unsigned int segment, unsigned int offset){
	unsigned char pattern;								/*Patron de prueba*/
	int i = 0;				
	for(pattern = 1; pattern != 0; pattern <<=1){		/*El patron recorre cada line bite por bite*/
		poke(segment, offset, pattern);					/*Se introduce el patro establecido en la direccion indicada*/
		if(peek(segment, offset) != pattern){			/*Comprueba si los datos en la seccion de memoria no coinciden con el patron*/
			puts("Eror en ducto D: ");					/*De no coincidir indica un erro en el ducto de datos*/
			putchar((char)i+'0');						/* que es indicado por la cantidad de bits recorridos*/
			puts("\r\n");		
		}
		i++;
	}
}

/*Test para el bus de direcciones*/
void addressBusTest(unsigned int segment, unsigned int offset, unsigned int nBits){
	unsigned int addresMask = nBits/sizeof(unsigned int)-1;			
	unsigned int offsetb;
	unsigned int testOffset;
	unsigned char pattern = 0xAA;
	unsigned char antipattern = 0x55;
	unsigned int bad_pins = 0;
	for(offsetb = 1 ; (offsetb & addresMask)!= 0; offsetb<<=1)
		poke(segment, offset+offsetb, pattern);
	
	testOffset = 0;
	poke(segment, offset+offsetb, antipattern);
	for(offsetb = 1; (offsetb & addresMask) != 0; offsetb <<= 1){
		if(peek(segment, offset+offsetb) != pattern)
			bad_pins = bad_pins | offsetb;
	}

	poke(segment, offset+offsetb, pattern);
	for(testOffset = 1; (testOffset & addresMask) !=0; testOffset <<= 1){
		poke(segment, offset+offsetb, antipattern);
		if((peek(segment, offset+offsetb) != pattern)){
			bad_pins = bad_pins | offsetb;		
		}
		for(offsetb = 1; (offsetb & addresMask) != 0; offsetb <<= 1){
			if((peek(segment, offset+offsetb)) && (offsetb != testOffset))
				bad_pins = bad_pins | offsetb;
		}
		poke(segment, offset+offsetb, pattern);
	}
	puts("\r\n");
	printBin((unsigned char)(bad_pins >> 8));
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