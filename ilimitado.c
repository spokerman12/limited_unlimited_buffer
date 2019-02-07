/* 
 * Universidad Simon Bolivar
 * Departamento de Computación y Tecnologı́a de la Información
 * Sistemas de Operacion I - CI3825
 * Trimestre Enero-Marzo 2018
 *
 * Simulacion del problema de productor/consumidor
 * con buffer ilimitado o limitado.
 * 
 * 
 * Ultima modificacion: 12.04.2018
 *
 * @Autor: Daniel Francis. 12-10863
 *
 *
 * Propuesto en el Stallings - Operating Systems. Capitulo 5
 *
 *  Hay uno o mas productores generando algun tipo de dato
 *  y los colocan un un bufer.
 *
 *  Existe un solo consumidor que toma elementos del bufer, uno a la vez.
 * 	El sistema ha de ser limitado para prevenir la superposicion de
 *	operaciones de bufer (un solo agente, sea productor o consumidor,
 *	puede acceder al bufer a la vez).
 *
 */

/*
 *	Caso ilimitado - Solucion: Semaforos binarios
 *
 *	Se puede experimentar con los sleep() del productor
 *	y del consumidor probar diferentes casos de velocidad
 *	de produccion/consumo.
 *
 *				
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

int bsem_s = 0;
int bsem_d = 0;

void bsem_wait(int bsem)
{
	while (bsem == 1)
	{
		sleep(1);
		if (bsem!=1)
			break;
	}
    
}

void bsem_post(int bsem)
{
    bsem = 0;
}

int buffer = 0;
int n = 0;

void * productor()
{
	int countdown = 10;

	while(countdown > 0)
	{
		countdown--;

		// Produce
		printf("Produce. Buffer en %d\n",buffer);
		//sleep(1);
		
		bsem_wait(bsem_s);
		
		// Append
		buffer++;
		printf("Append. Buffer en %d\n",buffer);

		n++;
		if (n==1)
		{
			bsem_post(bsem_d);
		}
		bsem_post(bsem_s);
		sleep(3);
	}


}

void * consumidor()
{
	int m;
	int countdown = 10;
	bsem_wait(bsem_d);

	while(countdown > 0)
	{
		countdown--;
		bsem_wait(bsem_s);

		// Take
		buffer--;
		if (buffer<0)
			bsem_wait(bsem_s);

		printf("Take. Buffer en %d\n",buffer);

		n--;
		m = n;
		bsem_post(bsem_s);

		// Consume
		printf("Consume. Buffer en %d\n",buffer);

		if(m==0)
		{
			bsem_wait(bsem_d);
		}
		sleep(5);
	}

}

int main()
{
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1,NULL,productor,NULL);
	pthread_create(&thread2,NULL,consumidor,NULL);

	sleep(60);

}





