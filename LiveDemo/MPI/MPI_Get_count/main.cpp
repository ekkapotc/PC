#include <cstdio>
#include <cstdlib>
#include <mpi.h>
 
/**
 * @brief Illustrates how to retrieve the number of elements in a message
 * received.
 * @details This application is meant to be run with 2 processes: a sender and
 * a receiver.
 **/
enum role { SENDER, RECEIVER };

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(size != 2)
    {
        if(rank==0){
            printf("This application is meant to be run with 2 processes.\n");
        }
        //MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        MPI_Finalize();
        return EXIT_SUCCESS;
    }
    
    switch(rank)
    {
        case SENDER:
        {
            int buffer[4] = {0,1,2,3};
            MPI_Send(buffer,4, MPI_INT, RECEIVER, 0, MPI_COMM_WORLD);
            break;
        }
        case RECEIVER:
        {
            int buffer[4];
            MPI_Status status;
            MPI_Recv(buffer, 4, MPI_INT, SENDER, 0, MPI_COMM_WORLD, &status);
            
    
            int count;
            MPI_Get_count(&status, MPI_INT, &count);
            printf("Number of elements retrieved from the status object: %d.\n", count);
            
            printf("Buffer Contents:");
            for(int i=0;i<count;i++)
                printf(" %d ",buffer[i]);
            printf("\n");
            
            break;
        }
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
