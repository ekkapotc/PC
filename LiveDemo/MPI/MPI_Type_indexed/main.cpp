#include <mpi.h>
#include <cstdio>
#include <cstddef>
struct Partstruct
{
    char c;
    double d[6];
    char b[7];
};

enum role{SENDER, RECEIVER};

int main(int argc,char ** argv){

    MPI_Init(&argc,&argv);
    
    int rank,size;
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    if(size!=2){
        printf("This application is meant to be run with 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    
    int mat[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
    int displacements[3] = {0,3,6};
    int block_lengths[3] = {1,2,3};
    
    MPI_Datatype lower_triangular_type;
    MPI_Type_indexed(3,block_lengths,displacements,MPI_INT,&lower_triangular_type);
    MPI_Type_commit(&lower_triangular_type);
    
    switch(rank){
        
        case SENDER:
            
            MPI_Send(mat,1,lower_triangular_type,RECEIVER,123,MPI_COMM_WORLD);
            
            break;
            
        case RECEIVER:
            
            MPI_Recv(mat,6,MPI_INT,SENDER,123,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            
            for( int i=0;i<3;i++){
                
                for( int j=0;j<3;j++){
                    printf("mat[%d][%d] = %d ",i,j,mat[i][j]);
                }
                
                printf("\n");
            }
            
            break;
    }
    
    MPI_Finalize();
    
    return EXIT_SUCCESS;
}
