#include <mpi.h>
#include <cstdio>

int main(int argc,char ** argv){

  MPI_Init(&argc,&argv);
  
  int rank,size;
  
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(size!=2){
      if(!rank)
      	printf("This program is meant to run with 2 processes\n");
      MPI_Finalize();
      return 0;
  }

  enum role{ PING , PONG };

  int my_role  = rank==0 ? PING : PONG;

  int buff = 9;

  switch(my_role){
	case PING:
		printf("Rank %d is sending %d...\n",rank,buff);
		MPI_Send(&buff,1,MPI_INT,PONG,100,MPI_COMM_WORLD);
		MPI_Recv(&buff,1,MPI_INT,PONG,200,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Rank %d received %d\n",rank,buff);
		break;
	case PONG:
		MPI_Recv(&buff,1,MPI_INT,PING,100,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Rank %d received %d\n",rank,buff);
		buff = -1*buff;
		printf("Rank %d is sending %d...\n",rank,buff);
		MPI_Send(&buff,1,MPI_INT,PING,200,MPI_COMM_WORLD);
		break;
  }

  MPI_Finalize();
  return 0;
}
