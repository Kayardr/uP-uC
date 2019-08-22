#include <stdio.h>
#include <time.h>

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

void initialization(pet *m_pet){						//Stats base
	m_pet->healt.current = 100;							//Salud inicial
	m_pet->healt.alarm = 60;							//Nivel minimo para alarma
	m_pet->healt.frecuency = 60;						//Tiempo con el que sieminuye salud
	
	//========== Alimentacion ============
	m_pet->feeding.current = 100;						//Alimentación inicial
	m_pet->feeding.alarm = 60;							//Alarma de alimento
	m_pet->feeding.frecuency = 60;						//Tiempo de disminución
	
	//========== Entretenimiento =========
	m_pet->entertain.current = 100;						//
	m_pet->entertain.alarm = 60;						//
	m_pet->entertain.frecuency = 60;	
	
	//========== Limpieza ================
	m_pet->cleaning.current = 100;						//
	m_pet->cleaning.alarm = 30;							//
	m_pet->cleaning.frecuency = 30;						//
	
}

int main(void){
	pet m_pet;
	time_t last = time(NULL);
	unsigned int s_elapsed = 0;
	initialization(&m_pet);

	while(1){
		if((time(NULL)-last)>=1){
			last = time(NULL);
			printf("%d\n", ++s_elapsed);
			printf("H = %i\t", m_pet.healt.current);
			printf("F = %i\t", m_pet.feeding.current);
			printf("E = %i\t", m_pet.entertain.current);
			printf("C = %i\t\n", m_pet.cleaning.current);
		}

		
		
		delay(200);
	}

	return 0;
}