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

double compute_sum(double * arr , size_t len){
   double sum = 0.0;
   for(auto i{0} ; i<len ; i++)
       sum += arr[i];
   return sum;
}

int main(int argc,char ** argv){
  
  srand(time(NULL));
  int elems_per_proc = atoi(argv[1]);
  
  int nprocs, rank;
    
  MPI_Init(&argc,&argv);
  
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
  
  double * random_nums = generate_array(elems_per_proc);
  
  double local_sum = compute_sum(random_nums,elems_per_proc);

  double global_sum;
  MPI_Reduce(&local_sum , &global_sum , 1 ,  MPI_DOUBLE , MPI_SUM , 0 , MPI_COMM_WORLD);

  if(!rank){
      printf("The average of all elements  is  %f\n",  global_sum/(elems_per_proc*nprocs));
  }

  delete [] random_nums;


  MPI_Finalize();
    
  return 0;
}
