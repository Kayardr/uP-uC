extern void putchar( char dato );
void gets(char *str);
void puts( char *str );
void itoa(unsigned int number, char* str, unsigned char base);
void itor(unsigned int number, char* str);
unsigned int atoi(char *str);

extern char getchar( void );
void printdec(unsigned char dato);


int div[] = {50000, 40000, 10000, 9000,5000,4000, 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
char* roman[] = {"(L)","(X)(L)", "(X)", "(I)(X)", "(V)", "(I)(V)","(I)", "C(I)", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

char jmp[]="\r\n";
char str[20];
char strb[20];

char in[] = "Input: ";
char hex[] = "Hex: ";
char bin[] = "Bin: ";
char rom[] = "Roman: ";
unsigned int b;
int main ( void ){
	while(1){
		puts(in);
		gets(str);
		b = atoi(str);
		puts(jmp);

		puts(hex);
		itoa(b, str, 16);
		puts(str);
		puts(jmp);

		puts(bin);
		itoa(b, str, 2);
		puts(str);
		puts(jmp);

		puts(rom);
		itor(b, strb);
		puts(strb);
		puts(jmp);
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
	char aux;
	int i=0;
	while((aux=getchar()) !='\r'){
		if(aux==8){
			if(i>0){
				putchar(' ');
				putchar(8);
				*str--;
				i--;
			}
		}
		else{
			*str++=aux;
			i++;
		}
	}
	*str=0;
	putchar('\'');
	puts(str-i);
	putchar('\'');
	/*do{
		*str = getchar();
	}while(*(str++) != '\r');
	*str = 0;*/
}

void itor(unsigned int number, char* str){
	
	int i = 0;
	int j;
	itoa(number, str, 10);
	puts(str);
	puts(jmp);
	if(number==0){
		*str++ = 'n';
		*str = 0;
	}
	else{
		while(number){
			while(number/div[i]){
				for(j=0; roman[i][j]!=0; j++)
					*str++ = roman[i][j];
				number -= div[i];
			}
			i++;
		}
		*str = '\0';	
	}
	
}

unsigned int atoi(char *str){
	if(*str){
		unsigned int count = 0;
		while(*str>='0' && *str<='9'){
			count = count*10+(*(str++))-'0';
		}
		return count;
	}
	return 0;
	
}