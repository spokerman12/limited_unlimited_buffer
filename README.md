
# Simulacion del problema de productor/consumidor con buffer ilimitado o limitado.


Ultima modificacion: 12.04.2018


Propuesto en el Stallings - Operating Systems. Capitulo 5

Hay uno o mas productores generando algun tipo de dato
y los colocan un un bufer.

Existe un solo consumidor que toma elementos del bufer, uno a la vez.
El sistema ha de ser limitado para prevenir la superposicion de
operaciones de bufer (un solo agente, sea productor o consumidor,
puede acceder al bufer a la vez).

Caso limitado - Solucion: Semaforos

Se recomienda hacer un esquema grafico de los semaforos
para comprobar el orden de espera, 
al igual que experimentar con los sleep.

			
Caso ilimitado - Solucion: Semaforos binarios

Se puede experimentar con los sleep() del productor
y del consumidor probar diferentes casos de velocidad
de produccion/consumo.
