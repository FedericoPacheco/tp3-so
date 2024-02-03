#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	key_t claveSiembra, claveCosecha;
	int idSiembra, idCosecha;
	
	claveSiembra = ftok(".", 'S');
	claveCosecha = ftok(".", 'C');

	idSiembra = msgget(claveSiembra, 0666);
	idCosecha = msgget(claveCosecha, 0666);

	msgctl(idCosecha, IPC_RMID, 0);
	msgctl(idSiembra, IPC_RMID, 0);	

	return 0;
}
