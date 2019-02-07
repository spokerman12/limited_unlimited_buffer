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
 *	Caso limitado - Solucion: Semaforos
 *
 *	Se recomienda hacer un esquema grafico de los semaforos
 *	para comprobar el orden de espera, 
 *  al igual que experimentar con los sleep.
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

sem_t s;
sem_t n;
sem_t e;

int buffer = 0;
int buffersize = 7;



void * productor()
{
	int countdown = 10;

	while(countdown > 0)
	{
		countdown--;
		
		// Produce
		printf("Produce. (Buffer en %d)\n", buffer);

		//sleep(2);

		sem_wait(&e);
		sem_wait(&s);
		
		// Append
		buffer++;
		printf("Append. (Buffer en %d)\n", buffer);
		sem_post(&s);
		sem_post(&n);

		sleep(3);
	}
}

void * consumidor()
{
	int m;
	int countdown = 10;

	while(countdown > 0)
	{
		sem_wait(&n);
		sem_wait(&s);

		// Take
		buffer--;
		printf("Take. (Buffer en %d)\n",buffer);
		sem_post(&s);
		sem_post(&e);
		sleep(4);
		
		// Consume
		printf("Consume. (Buffer en %d)\n",buffer);
		sleep(3);
	}

}

int main()
{
	pthread_t thread1;
	pthread_t thread2;
	sem_init(&s,0,1);
	sem_init(&n,0,0);
	sem_init(&e,0,buffersize);

	pthread_create(&thread1,NULL,productor,NULL);
	pthread_create(&thread2,NULL,consumidor,NULL);

	sleep(60);

}





