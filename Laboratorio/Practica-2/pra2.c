extern void putchar( char dato );
void gets(char *str);
void puts( char *str );
void itoa(unsigned int number, char* str, unsigned char base);
void itor(unsigned int number, char* str);
unsigned int atoi(char *str);

extern char getchar( void );
void printdec(unsigned char dato);

char jmp[]="\r\n";
unsigned char i=0;
char str[20];

char a[] = "48";
unsigned int b;
int main ( void ){
	while(1){
		gets(str);
		b = atoi(str);
		itoa(b, str, 10);
		puts(str);
		puts(jmp);
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
	char aux[20];
	int i=0;
	do{
		*(aux + i++) = (number % base) > 9 ? (number % base) + 55 : (number % base) + '0';
		number = number/base;
	}while(number > 0);
	while(i>0){
		*(str++) = *(aux + (--i));
	}
	*(str) = 0;
}

void gets(char *str){
	do{
		*str = getchar();
	}while(*(str++) != '\r');
	*str = 0;
}

/*void itor(unsigned int number, char* str){
	
}*/

unsigned int atoi(char *str){
	if(*str){
		unsigned int count = 0;
		while(*str>'0' || *str<'9' || *str!=0){
			count = count*10+(*(str++))-'0';
		}
		return count;
	}
	return 0;
	
}