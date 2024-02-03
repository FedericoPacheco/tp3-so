#include <stdio.h>
#include <sys/types.h>
#include <linux/ipc.h> 
#include <linux/sem.h>
//#include <sys/shm.h>
#define tamanioMemoria 32 

int main()
{
	key_t claveClubPrimario, claveClubSecundario, claveBandera;
	int semaforoClubPrimario, semaforoClubSecundario;	
	union semun arg;
   
	claveClubPrimario = ftok(".", 'P');
	claveClubSecundario = ftok(".", 'S');
	claveBandera = ftok(".", 'B');

	// crear e inicializar semaforos clubes
	semaforoClubPrimario = semget(claveClubPrimario, 1, 0666 | IPC_CREAT); 
	semaforoClubSecundario = semget(claveClubSecundario, 1, 0666 | IPC_CREAT);      
	
	arg.val = 1;
	semctl(semaforoClubPrimario, 0, SETVAL, arg);
	arg.val = 0;
	semctl(semaforoClubSecundario, 0, SETVAL, arg);

	// crear memoria compartida
	shmget(claveBandera, tamanioMemoria, IPC_CREAT | 0666); 

     	return 0;
}
