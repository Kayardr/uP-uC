#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

typedef struct pet_stats{
	int current;
	int alarm;
	unsigned int frecuency;
}stats;

typedef struct tamagotchi_pet{
	stats healt;
	stats feeding;
	stats entertain;
	stats cleaning;
}pet;

void delay(double delay_t){
	clock_t begining = clock();
	while((clock() - begining) < delay_t);
}

void initialization(stats *stat, int current, int alarm, int frecuency){
	stat->current = current;
	stat->alarm = alarm;
	stat->frecuency = frecuency;
}

void dismis(stats *stat, int dismis, int frecuency){
	if(stat->frecuency > 1)
		stat->frecuency -= 1;
	else if(stat->current >=0 ){
		stat->current -= dismis;
		if(stat->current < 0)
			stat->current = 0;
		stat->frecuency = frecuency;
	}
}

void increase(stats *stat, int increase){
	if(stat->current < 100){
		stat->current += increase;
		if(stat->current > 100)
			stat->current = 100;
	}
}

void interact(pet *m_pet, char c){
	switch(c){
		case 'm' :
			increase(&m_pet->healt, 5);
			break;
		case 'f' : 
			if(m_pet->healt.current > 60)
				increase(&m_pet->feeding, 10);
			break;
		case 'p' :
			if(m_pet->healt.current > 60 || m_pet->feeding.current >60) 
				increase(&m_pet->entertain, 5);
			break;
		case 'b' : 
			if(m_pet->healt.current > 60 || m_pet->feeding.current > 60 || 
				m_pet->entertain.current > 50)
				increase(&m_pet->cleaning, 100);
			break;
		default: break;
	}
}

int alarm(stats *stat, int min){
	if(stat->current <= min)
		return 1;
	return 0;
}

void print_stats(int count, char tag){
	printf("%c", tag);
	printf("|");
	for(int i = 0 ; i < (int)count/10 ; i++){
		printf("*");
	}
	for(int i = 0; i < (int)(100-count)/10; i++){
		printf(" ");
	}
	printf("|%d\n", count);

}

int main(void){
	pet m_pet;
	char command[20];
	int dead = 0;
	int show = -1;
	strcpy(command, "cls");
	time_t last = time(NULL);
	unsigned int s_elapsed = 0;
	initialization(&m_pet.healt, 50, 60, 60);
	initialization(&m_pet.feeding, 100, 60, 60);
	initialization(&m_pet.entertain, 100, 50, 60);
	initialization(&m_pet.cleaning, 100, 30, 30);
	char c;
	while(1){
		if(dead!=1){
			if(kbhit()){
				c = getch();
				if(c!='s'){
					interact(&m_pet, c);
				}
				else{
					show = show*-1;
				}
			}

			if((time(NULL)-last)>=1){
				system(command);
				last = time(NULL);
				dismis(&m_pet.healt, 5, 60);
				dismis(&m_pet.feeding, 3, 60);
				dismis(&m_pet.entertain, 5, 60);
				dismis(&m_pet.cleaning, 5, 30);
				if(m_pet.healt.current == 0 || m_pet.feeding.current == 0)
					dead = 1;

				printf("%d\n", ++s_elapsed);

				if(show==1){
					print_stats(m_pet.healt.current, 'H');
					print_stats(m_pet.feeding.current, 'F');
					print_stats(m_pet.entertain.current, 'P');
					print_stats(m_pet.cleaning.current, 'C');	
				}
				

				if(alarm(&m_pet.healt, 60) == 1){
					printf("HELP MEEEE!\n");
					printf("\n\n\n\n\n");
					printf("           ########\n");
					printf("        ###        ###\n");
					printf("     ###              ###\n");
					printf("   ##                    ##\n");
					printf("  #                        #\n");
					printf(" #        XX      XX        #\n");
					printf(" #        XX      XX        #\n");
					printf(" #                          #\n");
					printf(" #                          #\n");
					printf(" #                          #\n");
					printf("  #                        #\n");
					printf("   ##        ####        ##\n");
					printf("     ###              ###\n");
					printf("        ###        ###\n");
					printf("           ########\n");
				}
				else if(alarm(&m_pet.feeding, 60) == 1){
					printf("IM HUNGRY\n");
					printf("\n\n\n\n\n");
					printf("           ########\n");
					printf("        ###        ###\n");
					printf("     ###              ###\n");
					printf("   ##                    ##\n");
					printf("  #       @@      @@       #\n");
					printf(" #       @@@@    @@@@       #\n");
					printf(" #       @@@@    @@@@       #\n");
					printf(" #        @@      @@        #\n");
					printf(" #                          #\n");
					printf(" #                ***       #\n");
					printf("  #        #     ****      #\n");
					printf("   ##       #######      ##\n");
					printf("     ###              ###\n");
					printf("        ###        ###\n");
					printf("           ########\n");
				}
				else if(alarm(&m_pet.entertain, 50) == 1){
					printf("IM BORED\n");
					printf("\n\n\n\n\n");
					printf("           ########\n");
					printf("        ###        ###\n");
					printf("     ###              ###\n");
					printf("   ##                    ##\n");
					printf("  #       @@      @@       #\n");
					printf(" #       @@@@    @@@@       #\n");
					printf(" #       @@@@    @@@@       #\n");
					printf(" #        @@      @@        #\n");
					printf(" #                          #\n");
					printf(" #           ####           #\n");
					printf("  #        ##    ##        #\n");
					printf("   ##                   ##\n");
					printf("     ###              ###\n");
					printf("        ###        ###\n");
					printf("           ########\n");
				}
				else if(alarm(&m_pet.cleaning, 30) == 1){
					printf("IM DIRTY\n");

					printf("\n\n\n\n\n");
					printf("    $$    $########         $$   \n");
					printf("    $   ###        ###     $$$   \n");
					printf(" $   ###              ###   $$   \n");
					printf("  $##                    ##  $   \n");
					printf("  #  ;    @@      @@       #\n");
					printf(" #       @@@@    @@@@       #\n");
					printf(" #       @@@@    @@@@       #\n");
					printf(" #  ;;    @@      @@    ;;  #\n");
					printf(" #   ;;                     #\n");
					printf(" #                     ;    #\n");
					printf("  #        ########        #\n");
					printf("   ##                    ##\n");
					printf("     ###              ###\n");
					printf("        ###        ###\n");
					printf("           ########\n");
				}else{
					printf("\n\n\n\n\n");
					printf("           ########\n");
					printf("        ###        ###\n");
					printf("     ###              ###\n");
					printf("   ##                    ##\n");
					printf("  #       @@      @@       #\n");
					printf(" #       @@@@    @@@@       #\n");
					printf(" #       @@@@    @@@@       #\n");
					printf(" #        @@      @@        #\n");
					printf(" #                          #\n");
					printf(" #       ############       #\n");
					printf("  #        ########        #\n");
					printf("   ##        ####        ##\n");
					printf("     ###              ###\n");
					printf("        ###        ###\n");
					printf("           ########\n");
				}
			}	
		}
		else{
			system(command);
			printf("YOUR PET HAS DIED\n" );
			printf("Elapsed time (seconds): %i\n", s_elapsed);
		}
		
		delay(200);
	}

	return 0;
}