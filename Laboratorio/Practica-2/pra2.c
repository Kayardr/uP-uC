extern void putchar( char dato );
void gets(char *str);
void puts( char *str );
void itoa(unsigned int number, char* str, unsigned char base);
void itor(unsigned int number, char* str);
unsigned int atoi(char *str);

extern char getchar( void );
void printdec(unsigned char dato);

char msg[]="Hola UABC\r\n";
unsigned char i=0;

int main ( void ){
	unsigned int number = 5;
	unsigned int base = 2;
	char str[20];
	while(1){
		printdec(i++);
		puts( msg );
		itoa(number, str, base);
		puts(str);
		getchar();
	}
	return 0;
}


void puts ( char *str ){
	while( *str )
		putchar( *str++ );
}

void printdec ( unsigned char dato ){
	putchar( dato/100 + 0x30 );
	dato%=100;
	putchar( dato/10 + 0x30 );
	putchar( dato%10 + 0x30 );
}

void itoa(unsigned int number, char* str, unsigned char base){
	do{
		*str++ = (number % base) + 30;
		putchar(*str);
	}while(number/base > base);
}

/*void itor(unsigned int number, char* str){

}*/

unsigned int atoi(char *str){
	unsigned int i=0;
	while(*str == 0)
		i = i * 10 + (*str++) - 30;
}