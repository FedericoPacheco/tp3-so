#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <linux/ipc.h> // si se coloca "sys" en lugar de "linux" no compila
#include <linux/sem.h> // idem

int main()
{
	key_t claveKit, claveHisopado, claveResultado;
	int semaforoKit, semaforoHisopado, semaforoResultado;
	union semun arg;
   
	claveKit = ftok(".", 'K');
	claveHisopado = ftok(".", 'H');
	claveResultado = ftok(".", 'R');
     
   	// crear semaforos
	semaforoKit = semget(claveKit, 1, 0666 | IPC_CREAT);    
	semaforoHisopado = semget(claveHisopado, 1, 0666 | IPC_CREAT);
	semaforoResultado = semget(claveResultado, 1, 0666 | IPC_CREAT);
   
   	// inicializar semaforos
	arg.val = 0;
	semctl(semaforoKit, 0, SETVAL, arg);

	arg.val = 0;
	semctl(semaforoHisopado, 0, SETVAL, arg);

	arg.val = 1;
	semctl(semaforoResultado, 0, SETVAL, arg);
     
	return 0;
}
