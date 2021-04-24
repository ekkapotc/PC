#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv)
{
    int maxElements = 1048576;
    int * sendData = new int[maxElements];
    int * recvData = new int[maxElements];

    if(!sendData)
    {
        printf("Allocation failed...\n");
        return -1;
    }else if(!recvData){
	printf("Allocation failed...\n");
	return -2;
    }else
    {
        srand(time(NULL));
        
        for(int i = 0; i < maxElements; ++i)
          
       	  sendData[i] = rand();
    }

    int rank, size;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(size!=2)
    {
        if(!rank)
            printf("This program is meant to run with 2 processes...\n");
        
        MPI_Finalize();
        return 0;
    }

    int nextRank = (rank+1)%size;
    int prevRank = (rank-1+size)%size;

    for(int numElements = 512; numElements < maxElements; numElements += 512)
    {
        MPI_Status statuses[2];
	MPI_Request requests[2];

	printf("Rank %d sends %d elements of data now\n",rank,numElements);
	MPI_Isend(sendData, numElements, MPI_INT, nextRank, 99, MPI_COMM_WORLD, &requests[0]);

	printf("Rank %d receives %d elements of data now\n",rank,numElements);
        MPI_Irecv(recvData, numElements, MPI_INT, prevRank, 99, MPI_COMM_WORLD, &requests[1]);
	
	MPI_Waitall(2,requests,statuses);
	printf("Rank %d is done with %d elements of data now\n",rank,numElements);
    }

    delete [] recvData;
    delete [] sendData;

    MPI_Finalize();
    return 0;
}
