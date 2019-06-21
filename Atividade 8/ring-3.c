#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N   2
int main(int argc, char **argv)
{
    int max = 0, maxrank = -1;    
    int ordem = 0;
    int token=0, i;
    int arg0, arg1, arg2, arg3;

    srand(time(NULL));
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    for(i=0;i<N;i++) {
    if (!ordem)
    { 
        arg0 = 0;
        arg1 = -1;
        arg2 = world_size-1;
        arg3 = 1;
    }
    else
    { 
        arg0 = world_size - 1;
        arg1 = 1;
        arg2 = 0;
        arg3 = 0;
    }

    if (world_rank != arg0)
    {
        if(token > max) {
            max = token;
            maxrank = world_rank;
        }
        MPI_Recv(&token, 1, MPI_INT, world_rank + arg1, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", world_rank, token,
               world_rank + arg1);
    }
    else
    {
        token = rand() % 100;
    }

    if (!ordem)
    {
        MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0,MPI_COMM_WORLD);
    }
    else
    {
        if ((world_rank - 1) > -1)
        {
            MPI_Send(&token, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD);
        }
        else MPI_Send(&token, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD);
    }
    if (world_rank == arg0)
    {
        if(token > max) {
            max = token;
            maxrank = world_rank;
        }
        MPI_Recv(&token, 1, MPI_INT, arg2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", arg0, token, arg2);
	    printf("Maior elemento =  %d gerado por %d\n",  max, maxrank);
    }
    ordem = arg3;
	
}
    MPI_Finalize();
   
}
