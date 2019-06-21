/*atividade 9.1*/
#include <stdio.h>
#include "mpi.h"
#include <sys/time.h>

#define N 100000000
#define u 2.0

int main(int argc, char* argv[]) {
    double passo, resultado;
    double x, soma_local;
    double tempo;
    int rank, inicio, fim, size;
    int i;
   struct timeval start, end;

//inicia a comunicacao
    MPI_Init(&argc, &argv);

    //iIDdo processo comunicador
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //numero de processos comunicadores
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank==0) 
		gettimeofday(&start, NULL); //marca o inicio do processamento

    //calculo dos indices utilizados nos processos
    inicio= rank*(N/size);
    fim = inicio+ (N/size);
//inicializacao das variaveis
    passo = (u-1) / (double) N;
    resultado = 0;
    soma_local = 0;
//looping que calcula a soma local feita por cada processo
    for (i=inicio; i<fim; i++) {
            x=1+i*passo;
            soma_local = soma_local + 0.5*(1/x+1/(x+passo));
        }
//reducao, obtencao do valor final da soma
    MPI_Reduce(&soma_local, &resultado, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0){
	printf("ln de %f : %f\n",  u, passo*resultado);//imprime o resultado do logaritmo
    	gettimeofday(&end,NULL); //marca o final do processamento
	double tempExe = ((end.tv_sec-start.tv_sec) * 1000000u +
	end.tv_usec - start.tv_usec) / 1.e6;
	printf("Tempo de execucao: %.16g milisegundos\n", tempExe*1000);
    }
    MPI_Finalize();

    return 0;
}
