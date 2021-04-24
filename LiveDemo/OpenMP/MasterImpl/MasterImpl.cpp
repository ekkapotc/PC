#include <omp.h>
#include <iostream>


int main(int argc,char ** argv)
{
    
    #pragma omp parallel
    {
        #pragma omp master
        {
            std::cout << "Paralel Region #1 : I'm Thread " << omp_get_thread_num() << std::endl;
        }
    }
    
    #pragma omp parallel
    {
        if(omp_get_thread_num()==0)
            
             std::cout << "Parallel Region #2 : I'm Thread " << omp_get_thread_num() << std::endl;
    }
    
    return 0;
}
