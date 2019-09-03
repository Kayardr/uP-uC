extern unsigned char peek(unsigned int segment, unsigned int offset);
extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
extern void putchar( char dato );
extern unsigned char getchar( void );

void main(){
	unsigned char a;
	unsigned char b;
	getchar();
	a = 'a';
	poke(200, 200, a);
	b = peek(200, 200);
	putchar(b);
}