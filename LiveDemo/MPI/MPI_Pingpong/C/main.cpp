#include <mpi.h>
#include <cstdio>
#include <cstdlib>

#define MAX_ARR_LENGTH (1<<10)

int main(int argc , char ** argv)
{
  MPI_Init(&argc,&argv);

  int rank,size;

  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(size!=2){
	if(!rank) 
          printf("This program is meant to run with 2 processes...\n");
	MPI_Finalize();
	return 0;
  }

  enum role{PING,PONG};

  srand(MPI_Wtime()*50000+17*rank);

  int numberOfElementsToSend = rand()%MAX_ARR_LENGTH;
  int numberOfElementsToRecv;

  int * sendBuffer = new int[numberOfElementsToSend];

  for(int i=0;i<numberOfElementsToSend;i++)
	sendBuffer[i] = rand()%100;

  int * recvBuffer;

  MPI_Status status;

  switch(rank){
	  case PING:
		printf("Rank %d is about to send %d elements...\n",rank,numberOfElementsToSend);
		MPI_Send(sendBuffer,numberOfElementsToSend,MPI_INT,PONG,99,MPI_COMM_WORLD);
		

		MPI_Probe(PONG,101,MPI_COMM_WORLD,&status);
		MPI_Get_count(&status,MPI_INT,&numberOfElementsToRecv);
		recvBuffer = new int[numberOfElementsToRecv];
		MPI_Recv(recvBuffer,numberOfElementsToRecv,MPI_INT,PONG,101,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Rank %d recieved the contents of length %d\n",rank,numberOfElementsToRecv);
		
		break;
	  case PONG:
		
		MPI_Probe(PING,99,MPI_COMM_WORLD,&status);
		MPI_Get_count(&status,MPI_INT,&numberOfElementsToRecv);
		recvBuffer = new int[numberOfElementsToRecv];
		MPI_Recv(recvBuffer, numberOfElementsToRecv, MPI_INT,PING,99,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("rank %d received the contents of length %d\n",rank,numberOfElementsToRecv);

		printf("Rank %d is about to send %d elements...\n",rank,numberOfElementsToSend);
		MPI_Send(sendBuffer,numberOfElementsToSend,MPI_INT,PING,101,MPI_COMM_WORLD);

		break;
  }

  delete [] recvBuffer;
  delete [] sendBuffer;

  MPI_Finalize();
  return 0;
}
