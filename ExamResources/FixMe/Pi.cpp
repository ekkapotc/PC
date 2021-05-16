#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <omp.h>


#define NUMITERATIONS 1000000000


int main(int argc, char *argv[])
{
    double totalCount = NUMITERATIONS;
    double totalHits = 0;
    unsigned int seedVal;
    
    
    std::cout << "\tThe number of processors available      = " << omp_get_num_procs() << std::endl;
    std::cout << "\tThe number of threads available         = " << omp_get_max_threads() << std::endl;;
    std::cout << "\tThe number of Monte Carlo iterations    = " << totalCount << std::endl;

    
    struct timespec startTime, endTime;
    clock_gettime(CLOCK_REALTIME, &startTime);
   
    #pragma omp parallel default(none) private(seedVal) shared(totalHits) 
    {
        seedVal = omp_get_thread_num();//Each thread seeds with its own thread id.
        
        #pragma omp for 
        for(int i=0 ; i<NUMITERATIONS ; i++)
        {
        
            double  x = (double) rand_r(&seedVal) / (double) RAND_MAX;
            double  y = (double) rand_r(&seedVal) / (double) RAND_MAX;
        
            double result = std::sqrt((x*x) + (y*y));
      
            if(result<1.0){
                #pragma omp critical
                totalHits += 1.0;//check if the generated value is inside a unit circle.
            }
        }    
    }
   

    clock_gettime(CLOCK_REALTIME, &endTime);

    double runtime = (endTime.tv_sec-startTime.tv_sec)+(endTime.tv_nsec-startTime.tv_nsec)/1e9;

    double pi = 4.0*totalHits/totalCount;
   
    std::cout << std::fixed;

    std::cout << std::setprecision(6);
    
    std::cout << "The value of Pi is approximately " << pi << "." << std::endl;
    std::cout << "The program took " << runtime << " sec." << std::endl;
   
   return 0;
}
