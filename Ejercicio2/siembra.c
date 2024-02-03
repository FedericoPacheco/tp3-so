#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define periodosSiembra 15
#define cantidadProductosSinSoja 3

char productosSinSoja[cantidadProductosSinSoja] = {'M', 'L', 'G'};
int contadorSoja = 0;

struct producto_msgbuf
{
	long mtype;
	char nombreProducto;
};

char decidirSiembra();

int main()
{
	key_t claveSiembra, claveCosecha;
	int idSiembra, idCosecha;
	int i;
	char productoElegido;
	struct producto_msgbuf productoSiembra;
	
	claveSiembra = ftok(".", 'S');
	claveCosecha = ftok(".", 'C');

	// conectarse
	idSiembra = msgget(claveSiembra, 0666);
	idCosecha = msgget(claveCosecha, 0666); 
	
	srand(time(NULL));

	for (i = 0; i < periodosSiembra; i++)
	{
		msgrcv(idSiembra, &productoSiembra, sizeof(productoSiembra), 0, 0);   // recibir un mensaje vacio / msgtyp = 0 para recibir de cualquier tipo

		productoElegido = decidirSiembra();
		printf("Se recibio: libre. \nSe enviara a sembrar: %c\n", productoElegido);
		
		productoSiembra.nombreProducto = productoElegido;

		msgsnd(idCosecha, &productoSiembra, sizeof(productoSiembra), 0);
	}

	return 0;
}

char decidirSiembra()
{
	char ch;

	if (contadorSoja < 3)
	{
		contadorSoja++;
		ch = 'S';	
	}
	else
	{
		contadorSoja = 0;
		ch = productosSinSoja[rand() % cantidadProductosSinSoja];
	}

	return ch;
}



