#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h> 
#include <sys/sem.h>
#define cantidadColores 3
#define tamanioCadenaColor 4
#define tamanioMemoria 32 

char colores [cantidadColores][tamanioCadenaColor] = {"Nar", "Ver", "Vio"};

int main ()   // similar a clubPrimario.c, salvo por los semaforos y colores
{
	key_t claveClubPrimario, claveClubSecundario, claveBandera, idMemoriaCompartida;       
	int semaforoClubPrimario, semaforoClubSecundario;
	int i;
	char* memoriaCompartidaPtr;
	struct sembuf sembufDown = {0, -1, 0}; 
	struct sembuf sembufUp = {0, 1, 0};

	claveClubPrimario = ftok(".", 'P');
	claveClubSecundario = ftok(".", 'S');
	claveBandera = ftok(".", 'B');

	semaforoClubPrimario = semget(claveClubPrimario, 1, 0);   // conectarse al semaforo
	semaforoClubSecundario = semget(claveClubSecundario, 1, 0);

	// conectar el proceso al segmento
	idMemoriaCompartida = shmget(claveBandera, tamanioMemoria, IPC_CREAT); 
	memoriaCompartidaPtr = shmat(idMemoriaCompartida, 0, 0);          
	
	for (i = 0; i < cantidadColores; i++)
	{
		// entrar a la "region critica"
		semop(semaforoClubSecundario, &sembufDown, 1);   
		strcat(memoriaCompartidaPtr, colores[i]);
		sleep(1);    // retraso para que se pueda visualizar como se van agregando los colores
		semop(semaforoClubPrimario, &sembufUp, 1); 
		// salir
		
		printf("%s\n", colores[i]);
	}
	
	printf("\nBandera final: %s\n", memoriaCompartidaPtr);
	
	return 0;
}

