extern unsigned char peek(unsigned int segment, unsigned int offset);
extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
extern void putchar( char dato );
extern unsigned char getchar( void );

void main(){
	unsigned char a;
	a = getchar();
	poke(200, 200, a);
	a = peek(200, 200);
	
}