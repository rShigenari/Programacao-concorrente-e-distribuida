#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N   3

int main(int argc, char** argv) {
 MPI_Init(NULL, NULL);
  int world_rank;
  int world_size;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int token, i;
	for(i = 0; i< N; i++) {
		 
		if((i%2)==0){
		  if (world_rank != 0) {
			MPI_Recv(&token, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,
				     MPI_STATUS_IGNORE);
			printf("Process %d received token %d from process %d\n", world_rank, token,
				   world_rank - 1);
		  } else {
			token = -1;
		  }
		  MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0,
				   MPI_COMM_WORLD);

		  if (world_rank == 0) {
			MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD,
				     MPI_STATUS_IGNORE);
			printf("Process %d received token %d from process %d\n", world_rank, token,
				   world_size - 1);
		  }
		}
		else if(i%2!=0){
			  if (world_rank != world_size-1) {
				MPI_Recv(&token, 1, MPI_INT, world_rank+1, 0, MPI_COMM_WORLD,
						 MPI_STATUS_IGNORE);
				printf("Process %d received token %d from process %d\n", world_rank, token,
				world_rank+1);
			  } else {
				token = -1;
			  }
			  if((world_rank - 1) > -1) {
				MPI_Send(&token, 1, MPI_INT, world_rank - 1, 0,MPI_COMM_WORLD);
			  }
			  else MPI_Send(&token, 1, MPI_INT, world_size-1, 0,MPI_COMM_WORLD);
			  if (world_rank == world_size-1) {
				MPI_Recv(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				printf("Process %d received token %d from process %d\n", world_size-1, token, 0);
			  }}
	}
MPI_Finalize();
	  
}
