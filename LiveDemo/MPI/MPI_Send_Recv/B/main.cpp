#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv)
{
    int maxElements = 1048576;
    int * data = new int[maxElements];
    
    if(!data)
    {
        printf("Allocation failed...\n");
        
        return -1;
    }
    else
    {
        srand(time(NULL));
        
        for(int i = 0; i < maxElements; ++i)
            
       	 data[i] = rand();
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

        if(!rank)
	{
          printf("Rank %d sends %d elements of data now\n",rank,numElements);
          MPI_Send(data, numElements, MPI_INT, nextRank, 0, MPI_COMM_WORLD);
        
          printf("Rank %d receives %d elements of data now\n",rank,numElements);
          MPI_Recv(data, numElements, MPI_INT, prevRank, 0, MPI_COMM_WORLD,&status);
        
          printf("Rank %d is done with %d elements of data\n",rank,numElements);
	}else{
	  printf("Rank %d receives %d elements of data now\n",rank,numElements);
	  MPI_Recv(data, numElements, MPI_INT, prevRank, 0, MPI_COMM_WORLD, &status);

	  printf("Rank %d sends %d elements of data now\n",rank,numElements);
	  MPI_Send(data, numElements, MPI_INT, nextRank, 0, MPI_COMM_WORLD); 
	}
    }

    delete [] data;

    MPI_Finalize();
    return 0;
}
