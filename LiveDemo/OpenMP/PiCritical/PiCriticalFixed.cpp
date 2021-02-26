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

    double wall_time = omp_get_wtime ( );
   
    #pragma omp parallel default(none) shared(totalHits) private(seedVal) 
    {
        seedVal = omp_get_thread_num();//Each thread seeds with its own thread id.
        
        double localTotalHits = 0.0;//local sum
        
        #pragma omp for 
        for(int i=0 ; i<NUMITERATIONS ; i++)
        {
            double  x = (double) rand_r(&seedVal) / (double) RAND_MAX;
            double  y = (double) rand_r(&seedVal) / (double) RAND_MAX;
        
            double result = std::sqrt((x*x) + (y*y));
                
            if(result<1.0){
               localTotalHits += 1.0;//check if the generated value is inside a unit circle.
            }
            
        }    
        
        #pragma omp critical(update_total_hits)
        {//critical section
            totalHits += localTotalHits;//update the total hits from the local sum 
        }
    }
   

    double runtime = omp_get_wtime() - wall_time;
    
    double pi = 4.0*totalHits/totalCount;
   
    std::cout << std::fixed;

    std::cout << std::setprecision(6);
    
    std::cout << "The value of Pi is approximately " << pi << "." << std::endl;
    std::cout << "The program took " << runtime << " sec." << std::endl;
   
   return 0;
}
