#include "mpi.h"
#include <cstdio>

#define SIZE 4

int main(int argc, char **argv){
    
    int nprocs, rank, sendcount, recvcount, root;

    double sendbuf[SIZE][SIZE] = {
        {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}  
    
    };

    double recvbuf[SIZE];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if(nprocs == SIZE) {
    
        root = 0;
        
        sendcount = SIZE;
        recvcount = SIZE;
        
        MPI_Scatter(sendbuf,sendcount,MPI_DOUBLE,recvbuf,recvcount,MPI_DOUBLE,root,MPI_COMM_WORLD);

        printf("rank= %d  Results: %f %f %f %f\n",rank,recvbuf[0],recvbuf[1],recvbuf[2],recvbuf[3]);
    }
    else{
        printf("Must specify %d processors. Terminating.\n",SIZE);

    }

    MPI_Finalize();
    
    return 0;
}
