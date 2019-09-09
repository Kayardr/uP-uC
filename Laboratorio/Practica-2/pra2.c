extern void putchar( char dato );
void gets(char *str);
void puts( char *str );
void itoa(unsigned int number, char* str, unsigned char base);
void itor(unsigned int number, char* str);
unsigned int atoi(char *str);

extern char getchar( void );
void printdec(unsigned char dato);

char* romanb[] = {"(L)", "(X)(L)", "(X)", "(I)(X)", "(V)", "(I)(V)", "(I)", "C(I)", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
int div[] = {50000, 40000, 10000, 9000, 5000, 4000, 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

char jmp[]="\r\n";
char str[20];

unsigned int b;

char c;
int k;
int l;
int main ( void ){
	while(1){
		puts("Input: ");
		gets(str);
		b = atoi(str);
		puts(jmp);

		puts("Hex: ");
		itoa(b, str, 16);
		puts(str);
		puts(jmp);

		puts("Bin :");
		itoa(b, str, 2);
		puts(str);
		puts(jmp);

		puts("Roman: ");
		itor(b, str);
		puts(str);
		puts(jmp);
		puts(jmp);
	}
	return 0;
}


void puts ( char *str ){
	while( *str )
		putchar( *str++ );
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
	const char *const aux = str;

	c = getchar();
	while((c!=13)){
		if(c==8){
			if(str!=aux){
				putchar(' ');
				putchar(c);
				str--;
			}
			else
				putchar(' ');
		}
		else if(str >= aux+20-1){
			putchar(8);
			putchar(' ');
			putchar(8);
		}
		else
			*(str++)=c;
		c=getchar();
	}
	*(str) = '\0';
	/*while((*(str++)=getchar())!= 13);
	*str = 0;*/
}

void itor(unsigned int number, char* str){
	k = 0;
	if(number==0){
		*str++ = 'n';
		*str = 0;
	}
	else{
		while(number){
			while(number/div[k]){
				for(l = 0; romanb[k][l]!=0; l++)
					*str++ = romanb[k][l];
				number -= div[k];
			}
			k++;
		}
		*str = 0;	
	}
}

unsigned int atoi(char *str){
	if(*str){
		unsigned int count = 0;
		while(*str>='0' && *str<='9'){
			count = (count*10)+((*(str++))-'0');
		}
		return count;
	}
	return 0;
}