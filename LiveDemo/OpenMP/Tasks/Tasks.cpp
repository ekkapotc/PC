#include <omp.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

#define MIN		0
#define MAX		100
#define NUM_ELEMS 	1000
#define CHUNK_SIZE 	100

/*
 * This function is not thread-safe so it should not be called inside a parallel region.
 */
void init_array(double * A){
   srand(time(NULL));
   for(int i=0;i<NUM_ELEMS;i++){
     A[i] = ((double) rand()*(MAX-MIN)/(double)RAND_MAX-MIN);
     //A[i] = i;
   }
}/*--- End of init_array routine ---*/

int main(int argc , char ** argv)
{

  double * A = new double[NUM_ELEMS];

  init_array(A);

  double sum = 0.0;

  for(int i=0;i<NUM_ELEMS;i++)
    sum += A[i];

  std::cout << "SUM = " << sum << std::endl;

  sum = 0.0;//reset 

  #pragma omp parallel default(none) shared(sum,A,std::cout)
  {
    #pragma omp for
    for(int i=0;i<NUM_ELEMS;i+=CHUNK_SIZE)
    {
      int start = i;
      int end = (i+CHUNK_SIZE-1<=NUM_ELEMS-1)? (i+CHUNK_SIZE-1) : (NUM_ELEMS-1);
      //int end = i+CHUNK_SIZE-1;

      #pragma omp critical (print_msg)
      std::cout << "Thread " << omp_get_thread_num() << " of " << omp_get_num_threads() <<  " produces Task(" << start << "," << end << ")." << std::endl;
  
      #pragma omp task  
      {
        double partial_sum = 0.0;

	#pragma omp critical (print_msg)
	std::cout << "Thread " << omp_get_thread_num() << " of " << omp_get_num_threads() << " executes Task(" << start << "," << end << ")." << std::endl; 

        for(int j=start;j<=end;j++)
	  partial_sum += A[j];

	#pragma omp critical (update_sum)
	sum += partial_sum; 
	

      }/*--- End of Task Construct ---*/
  
    }/*--- End of For Construct ---*/
  }/*--- End of Parallel Construct ---*/

  std::cout << "Sum = " << sum << std::endl;

  delete [] A;//deallocate A

  return 0;
}
