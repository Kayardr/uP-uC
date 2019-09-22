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

#define ALEN 0x7FF

void main(){
	unsigned char a;
	unsigned char b;
	a = getchar();
	poke(0, 0x2200, a);
	b = peek(0, 0x2200);
	putchar(b);
	getchar();
	dataBusTest(0, 0x2200);
	addressBusTest(0, 0x2200, 0x7FF);
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
			
			puts("\r\n");
			printBin(peek(segment, offset));
			puts("\r\n");
			printBin(pattern);
			puts("\r\n");
			puts("Eror en ducto D: ");					/*De no coincidir indica un erro en el ducto de datos*/
			putchar((char)i+'0');						/* que es indicado por la cantidad de bits recorridos*/
			puts("\r\n");		
		}
		i++;
	}
}

/*Test para el bus de direcciones*/
void addressBusTest(unsigned int segment, unsigned int offset, unsigned int nBits){
	unsigned int displacement;
	unsigned int aux_disp;
	unsigned int bad_pins = 0;
	unsigned char data = 1;
	for(displacement = 1; displacement < ALEN; displacement <<= 1)
		poke(segment, offset+displacement, 0);
	
	poke(segment, offset, 0x55);

	for(displacement = 1; displacement < ALEN; displacement <<= 1){
		if(peek(segment, offset+displacement)!=0)
			bad_pins |= offset;
	}

	for(displacement = 1; displacement < nBits; displacement <<= 1){
		poke(segment, offset, 0xFF);
		poke(segment, offset+displacement, data);

		for(aux_disp = displacement; aux_disp < nBits; aux_disp <<= 1){
			if(aux_disp != displacement){
				if(data == peek(segment, offset+aux_disp))
					bad_pins |= displacement;
			}
		}

		if(data != peek(segment, offset+displacement))
			bad_pins |= displacement;

		if(data == peek(segment, offset))
			bad_pins |= displacement;
		data++;
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