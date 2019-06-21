#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 10000000
#define max_th 8

typedef struct thread_information{ 
    int thread_id; 
    int start; 
    int end; 
} Tdado; 

double *vet1;
double *vet2;
double somaTotal = 0.0;
Tdado thread_interval[max_th]; 
pthread_mutex_t mutex;

void *somaVet(void *t_inf) {
    int i;
    double somaParcial = 0.0;
    Tdado *inf = (Tdado*) t_inf;

    for(i = inf->start; i <= inf->end; i++) 
        somaParcial += vet1[i]*vet2[i];

    pthread_mutex_lock(&mutex); //entra na região critica
        somaTotal += somaParcial;
    pthread_mutex_unlock(&mutex);
    
}

int main() {
    pthread_t t[max_th];
    int i, ratio = N/max_th, seed;
    double value;
    vet1 = (double*) malloc(N*sizeof(double));
    vet2 = (double*) malloc(N*sizeof(double));
    
    struct timeval inicio, final2;
    int tmili;	
    for(i = 0; i < N; i++) {
        seed = time(NULL);
 	seed = time(NULL);
        vet1[i] = value;
	value = (unsigned int) (rand_r(seed)%10);
        vet2[i] = value; 
    }
        
    for(i = 0; i < max_th; i++) {
        thread_interval[i].thread_id = i;
        thread_interval[i].start = ratio*i; 
            thread_interval[i].end = ((i!=(max_th-1)) ? ((ratio*(i+1))-1) : N-1);
    }
     gettimeofday(&inicio, NULL);
    for(i = 0; i < max_th; i++)  
            pthread_create(&t[i], NULL, &somaVet, (void *)&thread_interval[i]); 
      
    for(i = 0; i < max_th; i++)  
            pthread_join(t[i],NULL);

    printf("%f\n", somaTotal); 
    gettimeofday(&final2, NULL);
  tmili = (int) (1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000);
  printf("tempo decorrido: %d milisegundos\n", tmili);	

    return(0);
}
