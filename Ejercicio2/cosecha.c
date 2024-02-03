#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#define parcelasDisponibles 3
#define periodosSiembra 15
#define cantidadProductos 4

struct producto_msgbuf
{
	long mtype;
	char nombreProducto;
};

void cosechar(struct producto_msgbuf*);

int main()
{
	key_t claveSiembra, claveCosecha;
	int idSiembra, idCosecha;
	int i;
	struct producto_msgbuf productoVacio = {1, '\0'};
	struct producto_msgbuf productoCosecha;
	
	claveSiembra = ftok(".", 'S');
	claveCosecha = ftok(".", 'C');

	// conectarse
	idSiembra = msgget(claveSiembra, 0666); 
	idCosecha = msgget(claveCosecha, 0666);
	
	for (i = 0; i < parcelasDisponibles; i++)
	{
		printf("Aviso: parcela lista para sembrar...\n");
		msgsnd(idSiembra, &productoVacio, sizeof(productoVacio), 0);
	}

	for (i = 0; i < periodosSiembra; i++)
	{
		msgrcv(idCosecha, &productoCosecha, sizeof(productoCosecha), 0, 0);   // msgtyp = 0 para recibir de cualquier tipo

		cosechar(&productoCosecha);

		msgsnd(idSiembra, &productoCosecha, sizeof(productoCosecha), 0);
	}
	
	return 0;
}

void cosechar(struct producto_msgbuf* producto)
{
	int i;	

	if (producto -> nombreProducto == 'S')
		printf("Nueva cosecha prioritaria (");
	else
		printf("Se ha cosechado (");

	for (i = 0; i < 10; i++)
		printf("%c", producto -> nombreProducto);
	printf(")\nAviso, porcion de parcela libre para nuevo elemento a sembrar...\n");  
}
