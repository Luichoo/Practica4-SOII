//
// Main.c
// Practica4
//
//
/*
Luis Antonio Blanco conde
Gustavo Contreras Mejia
Alejandro Octavio Salas Comparan
Gabriel Salom Fernandez
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ParallelMatrix.h"

int main(int argc, char** argv)
{
	
	//Variables a utilizar
	int M[2][6]={{10,50,200,1000,1200,1920},
				 {20,50,100,1000,1200,1080}};
	int NHilos[4] = {1, 2, 3, 4};
	int *M1, *M2, *M3, *M4, *R1, *R2;
	int NH, i, max;
	double F1[4][6], F2[4][6], F3[4][6], F4[4][6];
	struct timespec time1, time2;
	/*Instrucciones para realizar la simulacion con 1, 2, 3 y 4 hilos disponibles para 4 nucleos.*/
	for(NH = 0; NH < 4; NH++){
	//Instrucciones para utilizar una cantidad de hilos.	
	omp_set_num_threads(NHilos[NH]);
	printf("\n--------------------------------------------------------------------------------------------\n");
	//Instruccion para imprimir la cantidad de nucleos disponibles en la computadora
	printf("Nucleos disponibles: %d\n", omp_get_max_threads());
	//y la cantidad maxima de hilos que se solicitaron.
	printf("Hilos solicitados: %d\n", NHilos[NH]);

	printf("\n\n");
	/*Instrucciones para realizar la simulacion con matrices de
	10 x 20
	50 x 50
	200 x 100
	1000 x 1000
	1200 x 1200
	1920 x 1080.
	*/
	for(i = 0; i < 6; i++){
		//Funcion para inicializar las matrices.
			M1 = creaM(M[0][i], M[1][i]);
			M2 = creaM(M[0][i], M[1][i]);
			R1 = creaM(M[0][i], M[1][i]);
			M3 = creaM(M[0][i], M[1][i]);
			M4 = creaM(M[0][i], M[1][i]);
			R2 = creaM(M[0][i], M[1][i]);
			LlenaM(M1, M[0][i], M[1][i]);
			LlenaM(M2, M[0][i], M[1][i]);
			LlenaM(M3, M[0][i], M[1][i]);
			LlenaM(M4, M[0][i], M[1][i]);
			printf("\nDimensiones de las matrices: %d x %d\n\n", M[0][i], M[1][i]);
		
		//Funcion para sumar las matrices de forma no paralela y toma de tiempo.
		clock_gettime(CLOCK_MONOTONIC, &time1);
		R1 = SumMNoParalela(M1,M2,M[0][i], M[1][i]);
		clock_gettime(CLOCK_MONOTONIC, &time2);
		F1[NH][i] = (double)(time2.tv_sec-time1.tv_sec)+((double)(time2.tv_nsec-time1.tv_nsec)/1000000000L);
		//Funcion para sumar las matrices de forma paralela y toma de tiempo.
		clock_gettime(CLOCK_MONOTONIC, &time1);
		R2 = SumMParalela(M3,M4,M[0][i], M[1][i],NHilos[NH]);
		clock_gettime(CLOCK_MONOTONIC, &time2);
		F2[NH][i]=(double)(time2.tv_sec-time1.tv_sec)+((double)(time2.tv_nsec-time1.tv_nsec)/1000000000L);
		//Funcion para obtener el valor maximo de forma no paralela y toma de tiempo.
		clock_gettime(CLOCK_MONOTONIC, &time1);
		max = MaxNoParalela(R1,M[0][i], M[1][i]);
		clock_gettime(CLOCK_MONOTONIC, &time2);
		F3[NH][i]=(double)(time2.tv_sec-time1.tv_sec)+((double)(time2.tv_nsec-time1.tv_nsec)/1000000000L);
		printf("Maximo en no paralelo: %d\n", max);
		//Funcion para obtener el valor maximo de forma paralela y toma de tiempo.
		clock_gettime(CLOCK_MONOTONIC, &time1);
		max = MaxParalela(R2, M[0][i], M[1][i],NHilos[NH]);
		clock_gettime(CLOCK_MONOTONIC, &time2);
		F4[NH][i]=(double)(time2.tv_sec-time1.tv_sec)+((double)(time2.tv_nsec-time1.tv_nsec)/1000000000L);
		printf("Maximo en paralelo: %d\n", max);
		}

	}
		free(M1);
		free(M2);
		free(M3);
		free(M4);
		free(R1);
		free(R2);
	//Impresion de tabla de tiempos de TODA la simulacion.
	for(NH = 0; NH < 4; NH++){
	printf("\n--------------------------------------------------------------------------------------------\n");
		printf("Nucleos: %d\n\n",NH + 1);
		for(i = 0; i < 6; i++){
			
			printf("-Dimensiones de la matriz: %d x %d\n\n", M[0][i], M[1][i]);
			printf("-Suma: %f\n", F1[NH][i]);
			printf("-Suma en paralelo: %f\n", F2[NH][i]);
			printf("-Valor maximo: %f\n", F3[NH][i]);
			printf("-Valor maximo en paralelo: %f\n\n", F4[NH][i]);
			
		}
	}
	printf("\n--------------------------------------------------------------------------------------------\n");
	return EXIT_SUCCESS;
}
