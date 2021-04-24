#include <omp.h>
#include <iostream>

void f(){
    std::cout << "Thread " << omp_get_thread_num() << " is executing f()." << std::endl;
}

void g(){
    std::cout << "Thread " << omp_get_thread_num() << " is executing f()." << std::endl;
}

void h(){
    std::cout << "Thread " << omp_get_thread_num() << " is executing f()." << std::endl;
}


int main(int argc , char ** argv)
{
    #pragma omp parallel
    {
        
        #pragma omp single
        std::cout << "The number of threads : " << omp_get_num_threads() << std::endl;
        
        #pragma omp sections
        {
            #pragma omp section
            f();
            #pragma omp section
            g();
            #pragma omp section
            h();
        }
    }
    
    
    return 0;
}
