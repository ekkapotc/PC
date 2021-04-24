#include <omp.h>
#include <iostream>

int main(int argc,char ** argv){
 
    int tid = 0; 
    //The value of tid is 0

    #pragma omp parallel private(tid)
    {
        //The value of tid is undefined
        tid = omp_get_thread_num();
        //The value of tid is defined
        std::cout << "Thread " << tid << std::endl;
    
    }/*--- End of parallel region ---*/

    std::cout << "After the parallel region, tid = " << tid << std::endl;


    //The value of tid is undefined
    
    return 0;
}

