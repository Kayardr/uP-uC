#include <time.h>
#include <conio.h>
#include <stdio.h>
void getsE161(char *str);
char getKey(char a, int times);

#define TIME 1000
#define MTIME 4

const char tc00[2] = {'1', ';'};
const char tc01[4] = {'2', 'A', 'B', 'C'};
const char tc02[4] = {'3', 'D', 'E', 'F'};

const char tc10[4] = {'4', 'G', 'H', 'I'};
const char tc11[4] = {'5', 'J', 'K', 'L'};
const char tc12[4] = {'6', 'M', 'N', 'O'};

const char tc20[5] = {'7', 'P', 'Q', 'R', 'S'};
const char tc21[4] = {'8', 'T', 'U', 'V'};
const char tc22[5] = {'9', 'W', 'X', 'Y', 'Z'};

const char tc30[2] = {'0', ' '};

char str[80];

int main(void){
	while(1){
		getsE161(str);
		putchar(13);
		putchar(10);
		printf("%s\n", str);
	}
	return 0;
}

void getsE161(char *str){
	char a = 0;
	char i = 0;
	int times = 0;
	clock_t last = 0;
	int upercase = 0;
	while(a!='D', a!='d'){

		if(kbhit() || (clock()-last) <= TIME){

			a = getch();
			if(a=='D' || a == 'd')
				break;
			else if(a>='0' || a<='9' || a == 'b' || a=='B' || a=='c' || a=='C'){	/*Siempre y cuando no sea enter*/
				if(a == 'b' || a == 'B' && i>0){ 									/*BORAR*/
						times = 0;
						str[i-1] = 0;
						i--;
						last = 0;
						putchar(8);
						putchar(0);
						putchar(8);
				}
				else if(a=='c' || a=='C'){
					upercase = (upercase+1)%2;
				}
				else if((clock()-last) <= TIME && last!=0){							/*Aun no se acaba el tiempo*/
					
					if(getKey(a, times)+32*upercase != str[i-1]){ 					/*Escribir si son diferentes*/
						times = 0;
						putchar(getKey(a, times)+32*upercase);
						str[i++] = getKey(a, times)+32*upercase;
						last = clock();
					}	
					else{															/*Cambiar si son iguales*/
						times++;
						putchar(8);
						putchar(getKey(a, times)+32*upercase);
						str[i-1] = getKey(a, times)+32*upercase;
						last = clock();
					}
				}
				else if((clock()-last) >= TIME && last!=0){							/*Se acabo el tiempo*/
					last = 0;
					times = 0;
				}
				else{																/*Se escribio por primera vez o despues de un rato*/
					times=0;
					
					putchar(getKey(a, times)+32*upercase);
					str[i++] = getKey(a, times)+32*upercase;
					last = clock();
				}
			}
		}
	}
	str[++i] = 0;
}

char getKey(char a, int times){
	switch(a){
		case '1' :
			return tc00[(times)%2];
			break;
		case '2' :
			return tc01[(times)%4];
			break;
		case '3' :
			return tc02[(times)%4];
			break;
		case '4' :
			return tc10[(times)%4];
			break;
		case '5' :
			return tc11[(times)%4];
			break;
		case '6' :
			return tc12[(times)%4];
			break;
		case '7' :
			return tc20[(times)%5];
			break;
		case '8' :
			return tc21[(times)%4];
			break;
		case '9' :
			return tc22[(times)%5];
			break;
		case '0' :
			return tc30[(times)%2];
			break;
		case '*' :
			return '*';
			break;
		case '#' :
			return '#';
			break;
		default :
			break;
	}
}