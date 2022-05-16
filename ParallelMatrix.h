//
// ParallelMatrix.h
// Practica4
//
//

#pragma once

#ifndef ParallelMatrix_h
#define ParallelMatrix_h

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//Prototipos de funciones
int* creaM(int,int);
int* SumMNoParalela(int *M1, int *M2, int r, int c);
int* SumMParalela(int *M1, int *M2, int r, int c,int);
int MaxNoParalela(int *M, int r, int c);
int MaxParalela(int *M, int r, int c, int);
void LlenaM(int*, int, int);

#endif
