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
	key_t claveKit, claveResultado;
   	int semaforoKit, semaforoResultado;
	int i, j;
   	struct sembuf sembufDown = {0, -1, 0}; 
	struct sembuf sembufUp = {0, 1, 0};
         
   	claveKit = ftok(".", 'K');
	claveResultado = ftok(".", 'R');

   	semaforoKit = semget(claveKit, 1, 0); // conectarse a los semaforos creados en inicializarSemaforos.c
        semaforoResultado = semget(claveResultado, 1, 0);
   	
	// Acciones de kit propiamente
   	
	for (i = 1; i <= cantidadDias; i++)
	{
		printf("Dia: %i\n", i);
		for (j = 1; j <= pacientesPorDia; j++)
		{
			semop(semaforoResultado, &sembufDown, 1);   // down(resultado)
			printf("1) Abriendo kit. Preparando... Persona: %i\n", j);
			sleep(1);
			semop(semaforoKit, &sembufUp, 1);           // up(kit)
			
		}
	}

	return 0;
}

