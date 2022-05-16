//
// ParallelMatrix.c
// Practica4
//
//

#include "ParallelMatrix.h"
#include <time.h>

//Definicion de funciones
int* creaM(int i, int j){
    return malloc((i*j)*sizeof(int*));
}
int* SumMNoParalela(int *M1, int *M2, int r, int c){
    int *R;
    R = creaM(r, c);
    for(int i = 0; i < r*c; i++)
        *(R + i) = *(M1 + i) + *(M2 + i);
    return R;

}
int* SumMParalela(int *M1, int *M2, int r, int c,int Hilos){
    int *R, i, j;
    R = creaM(r, c);
    #pragma omp parallel for num_threads(Hilos) private(i) 
    for(i = 0; i < r; i++){
        for(j=0;j<c;j++){
        *(R +(j+ c*i)) = *(M1 +(j+ c*i)) + *(M2 +(j+ c*i));
        }

    }

    return R;
}
int MaxNoParalela(int *M, int r, int c){
    int max = 0;
    for(int i = 0; i < r*c; i++){
        if(max < *(M + i))
            max = *(M + i);
    }
    return max;
}
int MaxParalela(int *M, int r, int c,int Hilos){
    int max = 0, i, j;
    #pragma omp parallel for num_threads(Hilos) private(i) private(j)shared(max)
    for(i = 0; i < r; i++){
        for(j=0;j<c;j++){
            if(max < *(M +(j+ c*i)))
                max = *(M +(j+ c*i));
        }       

    }

    return max;
}
void LlenaM(int *M,int r,int c){
    srand(time(NULL));
    for(int i = 0;i < r*c; i++)
        *(M + i) = rand() % 256;     
}