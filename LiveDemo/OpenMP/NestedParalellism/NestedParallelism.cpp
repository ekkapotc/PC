#include <iostream>
#include <string>
#include <omp.h>


int main(int argc,char** argv)
{
    std::cout << "Nested Parallelism : " << omp_get_nested() <<  std::endl;
  
    omp_set_nested(1);
  
    std::cout << "Nested Parallelism : " << omp_get_nested() <<  std::endl;
  
    #pragma omp parallel num_threads(2)
    {
        if(omp_get_thread_num()==0)
        {
            omp_set_num_threads(4);   
        }else
        {
            omp_set_num_threads(6); 
        }
        
        
        #pragma omp critical
        std::cout << "Thread " << omp_get_thread_num() << " inside the Parallel Region at Level 1 : " << omp_get_num_threads() << " : " << omp_get_max_threads() << std::endl;
      
        #pragma omp parallel
        {
            #pragma omp critical
            std::cout << "Thread " << omp_get_thread_num() << " inside the 1st Parallel Region at Level 2 : " << omp_get_num_threads() << " : " << omp_get_max_threads() << std::endl;
            
            omp_set_num_threads(8);//this will have no effect on next the parallel region as it only affects parallel regions at the same or any inner nesting level
          
        }
        
        #pragma omp parallel
        {
            #pragma omp critical
            std::cout << "Thread " << omp_get_thread_num() << " inside the 2nd Parallel Region at Level 2 : " << omp_get_num_threads() << " : " << omp_get_max_threads() << std::endl;
            
        }
               
    }
    
    return 0;
}
