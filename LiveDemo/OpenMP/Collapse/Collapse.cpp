#include <omp.h>
#include <iostream>


int main(void)
{   
    #pragma omp parallel for collapse(2)
    for(int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            #pragma omp critical
            std::cout << "I'm Thread " << omp_get_thread_num() << " : (" << i << "," << j << ")" << std::endl;
        }
    }

    return 0;
}  
