#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define MAX_THREADS 8

long N;

double *retorno;

int *vet;

void *calcula(void *tid) {
  int thid; 
  long i = thid;
  double result, maior, aux;

  thid = (int) tid;
  
  maior=0;
  while(i<N){
 	aux=vet[i];
	result = log10(aux);
	if(result>maior){
		maior=result;
	}
	i+=MAX_THREADS;
  }

  //printf("thread=%ld, maior local=%f\n", thid, result);

  retorno[thid] = maior;
}

int main(void){

  scanf("%ld",&N);

  double vf;

  pthread_t t[MAX_THREADS];
  long i;
  int th;
  struct timeval inicio, final2;
  int tmili,tmicro;

  vet = (int*) malloc(N*sizeof(int));

  retorno = (double*) malloc(MAX_THREADS*sizeof(double));



  srand(time(NULL));

  for(i=0;i<N;i++)
        vet[i]= rand()%N+1;

  gettimeofday(&inicio, NULL);


  for(th=0; th<MAX_THREADS; th++) {
    pthread_create(&t[th], NULL, &calcula, (void *) th);
  }


double max_total=0;

  for(th=0; th<MAX_THREADS; th++) {
    pthread_join(t[th],NULL);
   if(retorno[th]>max_total) max_total=retorno[th];
  }

  gettimeofday(&final2, NULL);

  tmili = (int) (1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000);	

  printf("%f\n",max_total);

  printf("%d\n", tmili);


  return 0;
}  
