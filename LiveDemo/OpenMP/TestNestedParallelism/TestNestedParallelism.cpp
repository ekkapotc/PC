#include <omp.h>
#include <iostream>

int main(int argc , char ** argv)
{
  if(omp_get_nested())
      
    std::cout << "Nested Parallelism is ON." << std::endl;
  
  else
      
    std::cout << "Nested Parallelism is OFF." << std::endl;
  
  #pragma omp parallel num_threads(omp_get_num_procs())
  {
    #pragma omp critical 
    std::cout << "Thread " << omp_get_thread_num() << " executes the outer parallel region." << std::endl;
    
    //omp_set_nested(false); //override the OMP_NESTED environment variable
    
    #pragma omp parallel num_threads(2)
    {
        
        #pragma omp critical 
        std::cout << "\tThread " << omp_get_thread_num() << " executes the inner parallel region." << std::endl;
        
    }/*--- End of Inner Parallel Region ---*/
    
      
  }/*--- End of Outer Parallel Region ---*/
  
  return 0;
}
