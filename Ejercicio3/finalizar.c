#include <stdio.h>
#include <sys/types.h>
#include <linux/ipc.h> 
#include <linux/sem.h>
//#include <sys/shm.h>
#define tamanioMemoria 32 

int main()
{
	semctl( semget( ftok(".", 'P'), 1, 0666) , 0, IPC_RMID, 0);
	semctl( semget( ftok(".", 'S'), 1, 0666) , 0, IPC_RMID, 0);  
	shmctl( shmget( ftok(".", 'B'), tamanioMemoria, 0666 ) , IPC_RMID, 0); 

     	return 0;
}
