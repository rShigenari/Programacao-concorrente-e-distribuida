/*atividade 9.2*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

#define tam 1.0
#define dx 0.00001
#define dt 0.000001
#define T    0.01
#define kappa 0.000045
MPI_Status status;

int main(int argc, char* argv[]) {

    double *tmp, *u, *u_prev;
    double x, t, tempo, maxval, max_global;
    long int i, n, maxloc, ini, fim, maxloc_global;
    int rank, size, prox, ant;
   struct timeval start, end;

    MPI_Init(&argc, &argv); //inicializa comunicacao

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //detecta o id do processo corrente
    MPI_Comm_size(MPI_COMM_WORLD, &size); //total de processos

   if (rank==0) 
	gettimeofday(&start, NULL); //marca o inicio da execucao

    n = (tam/dx)/size; //calcula a quantidade de pontos

    u = (double *) malloc((n + 1)*sizeof(double));
    u_prev = (double *) malloc((n + 1)*sizeof(double));

//define o valor inicial de x
    if(rank == 0)
	x = dx;
    else
        x = rank * (n+1) * dx; 

    //cada processi calcula o valor local
    for (i=1; i<n; i++) {
        if(x<=0.5){
            u_prev[i] = 200*x;
        }
        else{
            u_prev[i] = 200*(1.-x);
        }
        x += dx;
    }

    //acha os processos para interagir
    prox = rank + 1;
    ant = rank - 1;

    /* Ajusta o proximo do ultimo e o anterior do primeiro */
    if(rank == 0){
        ant = MPI_PROC_NULL; //define anterior do primeiro
    }
    if(rank == size -1){
        prox = MPI_PROC_NULL; //define proximo do ultimo
    }
//calcula o novo valor de u
    t = 0.;
    while (t<T) {
        x = dx;
        for (i=1; i<n; i++) {
            u[i] = u_prev[i] + kappa*dt/(dx*dx)*(u_prev[i-1]-2*u_prev[i]+u_prev[i+1]);
            if(u[i] >= 100) printf("%g\n", u[i]);
            x += dx;
        }

        //Envia ao prox e recebe do anterior 
        MPI_Sendrecv(&u[n-1], 1, MPI_DOUBLE, prox, 0,
                     &u_prev[0], 1, MPI_DOUBLE, ant, MPI_ANY_TAG,
                     MPI_COMM_WORLD, &status);

        // Envia ao anterior e recebe do proximo 
        MPI_Sendrecv(&u[1], 1, MPI_DOUBLE, ant, 0,
                     &u_prev[n], 1, MPI_DOUBLE, prox, MPI_ANY_TAG,
                     MPI_COMM_WORLD, &status);

        //forcando condicao de retorno
        if(rank == 0){
            u[0] = 0.;
            u_prev[0] = 0.;
        }
        else if(rank == size-1){
            u[n] = 0.;
            u_prev[n] = 0.;
        }

        u[0] = u_prev[0];
        u[n] = u_prev[n];

        tmp = u_prev; u_prev = u; u = tmp; 
        t += dt;
    }

    //acha o maior valor e sua localizacao
    maxloc = 1;
    for (i=1; i<n; i++) {
        if (u[i] > u[maxloc]){
            maxloc = i;
        }
    }

    maxval = u[maxloc];
    maxloc = (rank * (n+1)) + maxloc;

    if(rank != 0){
        MPI_Send(&maxval, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&maxloc, 1, MPI_LONG, 0, 1, MPI_COMM_WORLD);
    }
    else{
        long int* index = (long int*) malloc(size*sizeof(long int));
        double* val = (double*) malloc(size*sizeof(double));

        val[0] = maxval;
        index[0] = maxloc;
//receive
        for(i=1; i<size; i++){
            MPI_Recv(&val[i], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD,
                     &status);
            MPI_Recv(&index[i], 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD,
                     &status);
        }
        max_global = val[0];
        maxloc_global = index[0];
        for(i=1; i<size; i++){
            if(val[i] > max_global){
                max_global = val[i];
                maxloc_global = index[i];
            }
        }

        gettimeofday(&end,NULL); //marca o final da execucao
	double tempExe = ((end.tv_sec-start.tv_sec) * 1000000u +
	end.tv_usec - start.tv_usec) / 1.e6;
	printf("Tempo de execucao: %.16g (s)\n", tempExe);//imprime tempo
        printf("Max valor de u[%ld] = %g\n", maxloc_global, max_global); //imprime max
    }

    MPI_Finalize();
}
