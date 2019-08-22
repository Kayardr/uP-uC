#include <stdio.h>
#include <conio.h>
#include <time.h>

typedef struct pet_stats{
	int current;
	int alarm;
	time_t last_t;
	time_t current_t;
	long frecuency;
}stats;

typedef struct tamagotchi_pet{
	stats healt;
	stats feeding;
	stats training;
	stats cleaning;
}pet;

void delay(double delay_t){
	clock_t begining = clock();
	while((clock() - begining) < delay_t);
}

void initialization(pet *m_pet){
	
}

int main(void){
	stats m_stats;
	
	m_stats.last_t = time(NULL);
	m_stats.current_t = m_stats.last_t;

	while(1){
		

		printf("Elapsed time %u\n", m_stats.current_t - m_stats.last_t);
		m_stats.current_t = time(NULL);
		delay(100);
	}

	return 0;
}