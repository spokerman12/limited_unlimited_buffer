#Problema del productor/consumidor. Bufer limitado o ilimitado
all: LIMITADO ILIMITADO

LIMITADO: limitado.c
	gcc -o limitado limitado.c -pthread

ILIMITADO: ilimitado.c limitado
	gcc -o ilimitado ilimitado.c -pthread
