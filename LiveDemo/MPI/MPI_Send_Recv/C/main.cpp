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
        MPI_Status status;

	printf("Rank %d sends and receives %d elements of data now\n",rank,numElements);

	int tag = 99;
        
	MPI_Sendrecv(sendData, numElements, MPI_INT, nextRank, tag, 
		     recvData, numElements, MPI_INT, prevRank, tag,
		     MPI_COMM_WORLD, &status);
	
	printf("Rank %d is done with %d elements of data\n",rank,numElements);
    }

    delete [] recvData;
    delete [] sendData;

    MPI_Finalize();
    return 0;
}
