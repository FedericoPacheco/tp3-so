#include <sys/types.h>
#include <linux/ipc.h> 
#include <linux/sem.h>

int main()
{
	semctl( semget( ftok(".", 'K'), 1, 0666 ) , 0, IPC_RMID, 0);  
	semctl( semget( ftok(".", 'H'), 1, 0666 ) , 0, IPC_RMID, 0);  
	semctl( semget( ftok(".", 'R'), 1, 0666 ) , 0, IPC_RMID, 0);  
     
	return 0;
}
