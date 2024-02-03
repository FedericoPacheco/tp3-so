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
	key_t claveHisopado, claveResultado;
   	int semaforoHisopado, semaforoResultado;
	int i, j;
   	struct sembuf sembufDown = {0, -1, 0}; 
	struct sembuf sembufUp = {0, 1, 0};
         
	claveHisopado = ftok(".", 'H');
	claveResultado = ftok(".", 'R');

        semaforoHisopado = semget(claveHisopado, 1, 0);  // conectarse a los semaforos creados en inicializarSemaforos.c
	semaforoResultado = semget(claveResultado, 1, 0);
   	
	// Acciones de resultado propiamente
   	for (i = 1; i <= cantidadDias; i++)
	{
		printf("Dia: %i\n", i);
		for (j = 1; j <= pacientesPorDia; j++)
		{
			semop(semaforoHisopado, &sembufDown, 1);   // down(hisopado)
			printf("3) Almacenando muestra. Sellando resultado... Persona: %i\n", j);
			sleep(3);
			semop(semaforoResultado, &sembufUp, 1);    // up(resultado)
		}
	}

	return 0;
}

