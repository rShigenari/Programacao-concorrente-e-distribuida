#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 10000000
#define MAX_THREADS 8

typedef struct infoTh{ 
    int thread_id; 
    int ini; 
    int fim; 
} Tdado; 



double *vet1,  *vet2;
double somaTotal = 0.0;


int main(void) {
    pthread_t t[MAX_THREADS];
    int i;
    double somaVet, seed, valor;
    double ini, fim, run;	
    
    vet1 = (double*) malloc(N*sizeof(double));
    vet2 = (double*) malloc(N*sizeof(double));

    for(i = 0; i < N; i++) {
        seed = time(NULL);
        valor = rand_r(&seed)%100;
        vet1[i] = valor;
	valor = rand_r(&seed)%100;
        vet2[i] = valor; 
    }
     ini = omp_get_wtime();   
    omp_set_dynamic(0);     
    omp_set_num_threads(4); 
    #pragma omp parallel reduction(+:somaVet) private(i) 
    {
    #pragma omp  private(i)
    for(i = 0; i < N; i++) {
        somaVet += vet1[i]*vet2[i];
     }
    }

    printf("%.2f\n", somaVet); 
 

     fim = omp_get_wtime();
    printf("%f ms\n", (fim-ini)*1000);
    return(0);
}
