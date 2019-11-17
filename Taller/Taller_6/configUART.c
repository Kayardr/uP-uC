/*
    DESCRIPCIÓN
            Programa que, mediante el ingreso de datos por consola, configure el correspondiente puerto UART
    Creado por: Ricardo Castañon Renteria
*/
//Bibliotecas
#include <stdio.h>

//Dfiniciones
#define uint8_t     unsigned char
#define uint16_t    unsigned int
#define uint32_t    unsigned long int

//Funciones prototipo
void configUART(uint32_t fosc, uint8_t com, uint16_t baud, uint8_t nbits, uint8_t paridad, uint8_t paro, uint8_t u2x);
void writeUART(uint8_t n, uint8_t UCSRxn[], uint16_t UBRR);
void itoa(char* str, uint32_t number, uint8_t base);
uint32_t atouli(char *str);


int main(int argc, char *argv[]){
    uint32_t fosc;
    uint8_t com;
    uint16_t baud;
    uint8_t nbits;
    uint8_t paridad;
    uint8_t paro;
    uint8_t u2x;

    if(argc < 8){
        printf("No se han ingresado suficientes datos\n");
    }
    else{
        fosc =      atouli(argv[1]);
        com =       (uint8_t)atouli(argv[2]);
        baud =      (uint16_t)atouli(argv[3]);
        nbits =     (uint8_t)atouli(argv[4]);
        paridad =   (uint8_t)atouli(argv[5]);
        paro =      (uint8_t)atouli(argv[6]);
        u2x =       (uint8_t)atouli(argv[7]);
        configUART(fosc, com, baud, nbits, paridad, paro, u2x);
    }
    return 0;
}

void configUART(uint32_t fosc, uint8_t com, uint16_t baud, uint8_t nbits, uint8_t paridad, uint8_t paro, uint8_t u2x){
    
    uint8_t UCSRxn[3] = {0};
    uint16_t UBRR;
    if(u2x==0)
        UBRR = (uint16_t) (fosc / (uint32_t)baud / (uint32_t)16 ) - 1;
    else
        UBRR = (uint16_t) (fosc / (uint32_t)baud / (uint32_t)8 ) - 1;

    //CODIGO DE CONFIGURACION PARA UCSRAn
    if(u2x!=0)
        UCSRxn[0] |= (1<<1);
    //CODIGO DE CONFIGUACION PARA UCSRBn
    UCSRxn[1] |= 0xB8;
    //CODIGOS DE CONFIGURACION PARA UCSRCn
    //Bits de tamaño de datos
    switch(nbits){
        case 9:
            UCSRxn[1] |= (0b01 << 2);
            UCSRxn[2] |= (0b11 << 1);
            break;
        case 8:
            UCSRxn[2] |= (0b11 << 1);
            break;
        case 7:
            UCSRxn[2] |= (0b10 << 1);
            break;
        case 6:
            UCSRxn[2] |= (0b01 << 1);
            break;
        case 5:
            UCSRxn[2] &= ~(0b11 << 1);
            break;
        default: 
            break;
    }

    switch(paridad){
        case 0: UCSRxn[2] &= ~(0b11 << 4);
            break;
        case 1: UCSRxn[2] |= (0b01 << 4);
            break;
        case 2: UCSRxn[2] |= (0b10 << 4);
            break;
        case 3: UCSRxn[2] |= (0b11 << 4);
            break;
        default: 
            break;
    }

    switch(paro){
        case 1: UCSRxn[2] &= ~(0b1 << 3);
            break;
        case 2: UCSRxn[2] |= (0b1 << 3);
            break;
        default:
            break;
    }
    
    writeUART(com, UCSRxn, UBRR);
}

void writeUART(uint8_t n, uint8_t UCSRxn[], uint16_t UBRR){
    char nombre[] = "UART.C";
    char ports[] = "ABC";
    char aux[10];
    uint8_t i;
    
    //Apertura del archivo
    FILE *archivo = fopen(nombre, "a");

    if(archivo == NULL){
        printf("Error al abrir el archivo");
    }else{
        fprintf(archivo, "void configUART(){\n");
        itoa(aux, UBRR, 16);
        fprintf(archivo, "\tUBRR%dH = (uint8_t)(0x%s >> 8);\n", n, aux);
        fprintf(archivo, "\tUBRR%dL = (uint8_t)0x%s;\n", n, aux);
        for(i = 0; i < 3; i++){
            //Convertir UCSRxn a cadena
            itoa(aux, UCSRxn[i], 16);
            fprintf(archivo, "\tUCSR%c%d = 0x%s;\n",ports[i], n, aux);
        }
        fprintf(archivo, "}\n");
        fclose(archivo);
        printf("\n\nSe ha escrito correctamente el archivo!");
    }
}

void itoa(char* str, uint32_t number, uint8_t base){
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

uint32_t atouli(char *str){
    if(*str){
		uint32_t count = 0;
		while(*str>='0' && *str<='9'){
			count = (count*10)+((*(str++))-'0');
		}
		return count;
	}
	return 0;
}