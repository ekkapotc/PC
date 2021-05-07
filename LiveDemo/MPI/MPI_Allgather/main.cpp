#include <mpi.h>
#include <ctime>
#include <cstdio>

double * generate_array(int num_elems){
  double * random_nums = new double[num_elems];
  for(auto i {0};i<num_elems;i++){
    random_nums[i] = (rand() / (double)RAND_MAX);
  }
  return random_nums;
}

double compute_avg(double * arr , size_t len){
   double avg = 0.0;
   for(auto i{0} ; i<len ; i++)
       avg += arr[i];
   return avg/len;
}

int main(int argc,char ** argv){
  
  srand(time(NULL));
  int elems_per_proc = atoi(argv[1]);
  
  int nprocs, rank;
    
  MPI_Init(&argc,&argv);
  
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
  
  double * random_nums;
  
  if(!rank){//only the root has the array
    random_nums = generate_array(elems_per_proc*nprocs);
  }
  
  double * local_nums = new double[elems_per_proc];
  
  
  MPI_Scatter( random_nums , elems_per_proc , MPI_DOUBLE , local_nums , elems_per_proc , MPI_DOUBLE , 0 , MPI_COMM_WORLD );
  
  double local_avg = compute_avg( local_nums , elems_per_proc );
   
  double * local_avgs = new double[nprocs];

  MPI_Allgather(  &local_avg , 1 , MPI_DOUBLE , local_avgs , 1 , MPI_DOUBLE , MPI_COMM_WORLD );
  
  double parallel_avg = compute_avg(local_avgs,nprocs);
  printf("Parallel: the average of all elements is %f\n", parallel_avg);
  
  if(!rank){  
  	double serial_avg = compute_avg(random_nums,elems_per_proc*nprocs);
  	printf("Serial: the average of all elements is %f\n", serial_avg);
  }

  if(!rank)

    delete [] random_nums;

  delete [] local_nums; 
  delete [] local_avgs;
  
  MPI_Finalize();
    
  return 0;
}
