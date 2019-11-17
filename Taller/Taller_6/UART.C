void configUART(){
	UBRR0H = (uint8_t)(0x50 >> 8);
	UBRR0L = (uint8_t)0x50;
	UCSRA0 = 0x0;
	UCSRB0 = 0xB8;
	UCSRC0 = 0x1E;
}
void configUART(){
	UBRR0H = (uint8_t)(0xA1 >> 8);
	UBRR0L = (uint8_t)0xA1;
	UCSRA0 = 0x2;
	UCSRB0 = 0xB8;
	UCSRC0 = 0x1E;
}
