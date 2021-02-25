#include <omp.h>
#include <iostream>

int main(int argc,char** argv){
    
    #pragma omp parallel
    {
        std::cout << "The parallel region is executed by thread " << omp_get_thread_num() << std::endl;
        
        if(omp_get_thread_num()== 2)
        {
            std::cout << "Thread " << omp_get_thread_num() << " does things differently." << std::endl;
        }
        
    }/*--- End of parallel region ---*/
    
    return 0;   
}
