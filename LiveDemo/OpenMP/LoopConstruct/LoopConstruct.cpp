#include <omp.h>
#include <iostream>

int main(int argc,char** argv){
    
    int i,n = 1024;
    
    #pragma omp parallel shared(n), private(i)
    {
        #pragma omp for
        for(i=0;i<n;i++)
        {
            std::cout << "Thread " << omp_get_thread_num() << " executes loop iteration " << i << std::endl;
        }/*---End of parallel for ---*/
        
    }/*---End of parallel region ---*/
    
    return 0;
}
