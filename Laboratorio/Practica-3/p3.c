extern unsigned char peek(unsigned int segment, unsigned int offset);
extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
extern void putchar( char dato );
extern unsigned char getchar( void );
void puts ( char *str );

/*
Test
*/
void dataBusTest(unsigned int segment, unsigned int offset);


void main(){
	unsigned char a;
	unsigned char b;
	a = getchar();
	poke(200, 200, a);
	b = peek(200, 200);
	putchar(b);
	getchar();
	dataBusTest(200, 200);
	getchar();
}

void puts ( char *str ){
	while( *str )
		putchar( *str++ );
}

void dataBusTest(unsigned int segment, unsigned int offset){
	unsigned char pattern;
	int i = 0;
	for(pattern = 1; pattern != 0; pattern <<=1){
		poke(segment, offset, pattern);
		if(peek(segment, offset) != pattern){
			puts("Eror en ducto D: ");
			putchar((char)i+'0');
			puts("\r\n");
		}
		i++;
	}
}

void addressBusTest(unsigned int segment, unsigned int nBits){
	unsigned int addresMask = nBits/sizeof(unsigned int)-1;
	unsigned int offset;
	unsigned int testOffset;
	unsigned char pattern = 0xAA;
	unsigned char antipattern = 0x55;
	for(offset = 1 ; (offset & addresMask)!= 0; offset<<=1)
		peek(segment, offset, pattern);
}

