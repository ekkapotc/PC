#include <omp.h>
#include <iostream>

int main(int argc , char ** argv)
{    
    int i,n = 32;

    /*--- The declaration of i could have been done inside the parallel region to avoid the need to explicitly declare i as private. ---*/
    
    #pragma omp parallel default(none) shared(n,std::cout), private(i)
    {
        #pragma omp for
        for(i=0;i<n;i++)
        {
            std::cout << "Thread " << omp_get_thread_num() << " executes loop iteration " << i << std::endl;
        }/*---End of parallel for ---*/
        
    }/*---End of parallel region ---*/
    
    return 0;
}
