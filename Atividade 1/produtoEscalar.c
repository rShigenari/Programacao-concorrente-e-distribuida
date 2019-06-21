#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 1000
#define MAX_THREADS 4

double *arrayA;
double *arrayB;
double *retorno;

void *produtoEscalar(void *tid) {
  int thid;
  long i;
  double resultado;

  thid = (int) tid;

  for(i=thid; i<N; i+=MAX_THREADS)
     resultado +=  arrayA[i] * arrayB[i];

  printf("thread=%ld, resultado=%f\n", thid, resultado);

  retorno[thid] = resultado;
} 


int main(void){

  double value;

  pthread_t t[MAX_THREADS];
  long i;
  int th;
  struct timeval inicio, final2;
  int tmili;

  arrayA = (double*) malloc(N*sizeof(double));
  arrayB = (double*) malloc(N*sizeof(double));
  retorno = (double*) malloc(MAX_THREADS*sizeof(double));


  for(i=0;i<N;i++)
  {
        arrayA[i]= rand();
        arrayB[i]=rand();
  }

  gettimeofday(&inicio, NULL);

  for(th=0; th<MAX_THREADS; th++) {
    pthread_create(&t[th], NULL, &produtoEscalar, (void *) th);
  }


  for(th=0; th<MAX_THREADS; th++) {
    pthread_join(t[th],NULL);
    value += retorno[th];
  }

  gettimeofday(&final2, NULL);

  tmili = (int) (1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000);

  printf("tempo decorrido: %d milisegundos\n", tmili);

  printf("produto escalar=%f\n",value);



  return 0;
}  
