#include <omp.h>
#include <iostream>

int main(int argc,char ** argv){
 
    
    #pragma omp parallel
    {
        //The variable tid is declared here 
        int tid = omp_get_thread_num();
       
        std::cout << "Thread " << tid << std::endl;
    
    }/*--- End of the parallel region ---*/
    
    
    return 0;
}
