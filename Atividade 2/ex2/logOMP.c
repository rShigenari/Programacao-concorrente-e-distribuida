#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

//encontra o maior resultado da aplicação do LOG10, em OpenMP.
long N;


int *vet;

int main(void){

  scanf("%ld",&N);
  
  vet = (int*) malloc(N*sizeof(int)); 

  double max_total=0;

  long i = 0;
  struct timeval inicio, final2;
  int tmili,tmicro;


  srand(time(NULL));
  
  //calcula o log10 dos valores do vetor de entrada
  while(i<N){
	vet[i]= rand()%N+1;
	i++;
  }
        
  gettimeofday(&inicio, NULL);
  //criação de um pragma 
  #pragma omp parallel for private (i) num_threads(8)
  for(i=0;i<N;i++){
	if(log10(vet[i])>max_total){
		max_total=log10(vet[i]);
	}
  }
 

  gettimeofday(&final2, NULL);

  tmili = (int) (1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000);	
  //retorna o máximo
  printf("O máximo total será: %f\n",max_total);

  printf("%d\n", tmili);


  return 0;
}  
