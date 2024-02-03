#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	key_t claveSiembra, claveCosecha;
	int idSiembra, idCosecha;
	
	claveSiembra = ftok(".", 'S');
	claveCosecha = ftok(".", 'C');

	// crear colas de mensajes
	idSiembra = msgget(claveSiembra, 0666 | IPC_CREAT);
	idCosecha = msgget(claveCosecha, 0666 | IPC_CREAT);
	
	return 0;
}

