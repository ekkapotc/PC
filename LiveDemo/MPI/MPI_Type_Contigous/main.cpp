#include <mpi.h>
#include <cstdio>

enum role { SENDER, RECEIVER };

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
  
    int rank, size;
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(size != 2)
    {
        printf("This application is meant to be run with 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
   
    MPI_Datatype double_int_type;
    MPI_Type_contiguous(2, MPI_INT, &double_int_type);
    MPI_Type_commit(&double_int_type);
 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    switch(rank)
    {
        case SENDER:
        {
            int buffer_sent[2] = {12345, 67890};
            printf("MPI process %d sends values %d and %d.\n", rank, buffer_sent[0], buffer_sent[1]);
            MPI_Send(&buffer_sent, 1, double_int_type, RECEIVER, 0, MPI_COMM_WORLD);
            break;
        }
        case RECEIVER:
        {
            int received[2];
            MPI_Recv(&received, 2,MPI_INT, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("MPI process %d received values: %d and %d.\n", rank, received[0], received[1]);
            break;
        }
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
