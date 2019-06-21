#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


#define N 10000000


double *vet1, *vet2;
double somaTotal = 0;

int main(void) {

    int i;
    double somaVet, somaLocal, seed, value;
     double start, end, run;
    vet1 = (double*) malloc(N*sizeof(double));
    vet2 = (double*) malloc(N*sizeof(double));

    for(i = 0; i < N; i++) {
        seed = time(NULL);
        value = rand_r(&seed)%100;
        vet1[i] = value;
	value = rand_r(&seed)%100;
        vet2[i] = value;
    }

    start = omp_get_wtime();
    omp_set_dynamic(0);     
    omp_set_num_threads(8);
    #pragma omp parallel private(i) shared(somaTotal) 
    {
    somaLocal = 0.0;
    #pragma omp for
    for(i = 0; i < N; i++) {
        somaLocal += vet1[i]*vet2[i];
     }
    #pragma omp critical
    somaVet += somaLocal;
    }

    printf("%.2f\n", somaVet);
      end = omp_get_wtime();
    printf("%f ms\n", (end-start)*1000);

    return(0);
}
