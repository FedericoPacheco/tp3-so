#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#define pacientesPorDia 5
#define cantidadDias 2

int main()
{
	key_t claveHisopado, claveKit;
   	int semaforoHisopado, semaforoKit;
	int i, j;
   	struct sembuf sembufDown = {0, -1, 0}; 
	struct sembuf sembufUp = {0, 1, 0};
         
	claveHisopado = ftok(".", 'H');
	claveKit = ftok(".", 'K');

        semaforoHisopado = semget(claveHisopado, 1, 0); // conectarse a los semaforos creados en inicializarSemaforos.c
	semaforoKit = semget(claveKit, 1, 0);
   	
	// Acciones de hisopado propiamente
   	for (i = 1; i <= cantidadDias; i++)
	{
		printf("Dia: %i\n", i);
		for (j = 1; j <= pacientesPorDia; j++)
		{
			semop(semaforoKit, &sembufDown, 1);   // down(kit)
			printf("2) Tomando muestra. Hisopando ... Persona: %i\n", j);
			sleep(2);
			semop(semaforoHisopado, &sembufUp, 1);   // up(hisopado)   
		} 
	}       

	return 0;
}

