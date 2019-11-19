#ifndef UART
    #define UART

    #define BUFFER_SIZE     64
    #define FOSC            16E6
    #define GREEN           32
    #define YELLOW          33
    #define BLUE            34
    #define BASE            0xc0
    //Comprobacion del bufer
    //
    #define MOD(idx)                ((idx)&(BUFFER_SIZE-1))
    #define BUFFER_EMPTY(buffer)    (buffer.in_idx == buffer.out_idx)
    #define BUFFER_FULL(buffer)     (MOD(buffer.in_idx+1) == buffer.out_idx)
    #define SetBitPort(port, bit) __asm__ ( "sbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit) )
    #define ClrBitPort(port, bit) __asm__ ( "cbi %0, %1" : : "I" (_SFR_IO_ADDR(port)), "I" (bit) )


    typedef struct{
        char buffer[BUFFER_SIZE];           //Espacio reservado
        volatile unsigned char in_idx;      //Indice entrada (Head)
        volatile unsigned char out_idx;     //Indice salida (tail)
    } ring_buffer_t; 

    //Buffers (Recepcion y Transmision)
    /*extern ring_buffer_t RX;
    extern ring_buffer_t TX;*/

    uint8_t UART_avalaible();
    void UART_Init(uint8_t com, uint32_t baudrate, uint8_t size, uint8_t parity, uint8_t stop, uint8_t U2X);
    void UART_putchar(char data);
    char UART0_getchar(void);


    void UART0_gets(char *str);
    void UART0_puts(char *str);
    void UART0_itoa(char* str, uint16_t number, uint8_t base);
    uint16_t UART0_atoi(char *str);

    void clrscr(void);
    void setColor(uint8_t color);
    void gotoxy(uint8_t x, uint8_t y);
#endif
