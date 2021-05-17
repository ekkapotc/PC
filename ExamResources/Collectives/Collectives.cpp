#include <mpi.h>
#include <cstdio>
#include <cstdlib>

static int inspectRank = 0;


void simpleIntBcast(int *data, int count, int root, MPI_Comm comm)
{
    //TODO: use only MPI_Send and MPI_Recv to implement simpleIntBcast
}

void simpleIntScatter(int *sendbuf,int sendcount,int *recvbuf,int recvcount,
int root,MPI_Comm comm)
{
    //TODO: use only MPI_Send and MPI_Recv to implement simpleIntScatter
}

void simpleIntGather(int *sendbuf, int sendcount, int *recvbuf, int recvcount,
int root, MPI_Comm comm)
{
    //TODO: use only MPI_Send and MPI_Recv to implement simpleIntGather
}

int main(int argc,char** argv)
{
  int rank , nprocs;
  
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
  
  //check who will spect the outcome
  if(argc>1)
  {
    inspectRank = atoi(argv[1]);
    
    if(inspectRank < 0 || inspectRank >= nprocs)
        MPI_Abort(MPI_COMM_WORLD, 1);
    
  }
  
  //seed the RNG
  srand(MPI_Wtime()+79*rank);  
  //generate a rank-specific random number
  int randomNumber = rand()%100;
  
  printf("Rank %d has the random number %d\n",rank,randomNumber);
  
  
  //allocate send & receive buffers
  int * sendBuffer = new int[nprocs];
  int * recvBuffer = new int[nprocs];
  int data = -1;
  
  //use MPI_Barrier to synchronize the output to 'stdout'
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  
  /*---- Broadcast ----*/
  
  if(rank==inspectRank)
        printf("-------------------------------------\n"
              "Broadcast\n"
            "-------------------------------------\n");
  
  
  //prepare local data to be broadcast
  data = randomNumber;
  
  if(rank==inspectRank)
        printf("Rank %d:\tdata before simpleIntBcast is %d\n",
inspectRank,data);
  
  
  simpleIntBcast(&data,1,0,MPI_COMM_WORLD);
  
  if(rank==inspectRank)
        printf("Rank %d:\tdata after simpleIntBcast is %d\n",
inspectRank,data);
  
  
  //TODO:Insert an MPI_Broadcast call here to check if the outcome of your implementation is the same as that of MPI_Broadcast
  
  if(rank==inspectRank)
        printf("Rank %d:\tdata after MPI_BCast is %d\n",
inspectRank,data);
  

  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  
  /*---- Scatter ----*/
  
  if(rank==inspectRank)
        printf("-------------------------------------\n"
              "Scatter\n"
            "-------------------------------------\n");
  

  //prepare the local data based on the random number 
  for(int i = 0;i<nprocs;i++){
    sendBuffer[i] = randomNumber+i*1000;
  }

  data = -1;
  
  if(rank==inspectRank)
        printf("Rank %d:\tdata before simpleIntScatter is %d\n",
inspectRank,data);
  
  
  simpleIntScatter(sendBuffer,1,&data,1,0,MPI_COMM_WORLD);
  
  if(rank==inspectRank)
        printf("Rank %d:\tdata after simpleIntScatter is %d\n",
inspectRank,data);
  
  
  //TODO:Insert an MPI_Scatter call here to check if the outcome of your implementation is the same as that of MPI_Scatter
  
  if(rank==inspectRank)
        printf("Rank %d:\tdata after MPI_Scatter is %d\n",
inspectRank,data);
  

  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  
  /*---- Gather ----*/
  
  if(rank==inspectRank){
    printf("-------------------------------------\n"
              "Gather\n"
            "-------------------------------------\n");
  }
  
  //prepare the local data
  for(int i=0 ; i<nprocs ; i++)
    recvBuffer[i] = -1;
    
  data = randomNumber;
  
  if(rank==0)
  {
    printf("Rank %d:\trecvBuffer before SimpleIntGather is",
 0);
        
    for(int i = 0; i<nprocs; i++)
        printf(" %d",recvBuffer[i]);
    printf("\n");
  }
  
  simpleIntGather(&data,1,recvBuffer,1,0,MPI_COMM_WORLD);

  if(rank==0)
  {
    printf("Rank %d:\trecvBuffer after SimpleIntGather is",
 0);
    
    for(int i = 0; i<nprocs; i++)
        printf(" %i",recvBuffer[i]);
    printf("\n");
  }
  
  
  //TODO:Insert an MPI_Gather call here to check if the outcome of your implementation is the same as that of MPI_Gather
  
  if(rank==0)
  {
    printf("Rank %d:\trecvBuffer after MPI_Gather is",
 0);
    
    for(int i = 0; i<nprocs; i++)
        printf(" %i",recvBuffer[i]);
    printf("\n");
  }
  
  //free up the buffers
  delete [] sendBuffer;
  delete [] recvBuffer;
  
  MPI_Finalize();
  
  return 0;
}
