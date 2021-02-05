#include <cstdio>
#include <cstdlib>
#include <cmath> 
#include <pthread.h>
#include <iostream>
#include <iomanip>

#define NUMTHREADS    4        

#define NUMITERATIONS 1000000000   

void * calculate(void * arg)
{
    std::size_t tid =   reinterpret_cast<std::size_t>(arg);
    unsigned int seedVal = tid;
    double * totalHits   = new double();
    std::size_t samplePoints = NUMITERATIONS / NUMTHREADS;
    
    *totalHits = 0;
  
    for(std::size_t i=0 ; i<samplePoints ; i++){
       
        double  x = (double) rand_r(&seedVal) / (double) RAND_MAX;
        double  y = (double) rand_r(&seedVal) / (double) RAND_MAX;
        double result = std::sqrt((x*x) + (y*y));
      
        if(result<1.0){
            *totalHits += 1;         
        }
    }
   
    if(!tid){
        std::size_t remainder = NUMITERATIONS % NUMTHREADS;
      
        for(std::size_t i=0 ; i<remainder ; i++){
            double  x = (double) rand_r(&seedVal) / (double) RAND_MAX;
            double  y = (double) rand_r(&seedVal) / (double) RAND_MAX;
            double result = std::sqrt((x*x) + (y*y));
            
            if(result<1.0){
                *totalHits += 1;      
            }
        }
   }

   pthread_exit((void *)totalHits);     
}

int main(int argc, char * argv[])
{
    pthread_t tids[NUMTHREADS];
    double pi = 0.0;
    void * partialSol;
    struct timespec startTime, endTime;
    
    clock_gettime(CLOCK_REALTIME, &startTime);
   
    for(std::size_t i=0 ; i<NUMTHREADS ; i++)
    {
        pthread_create(&tids[i], NULL, &calculate , reinterpret_cast<void*>(i));
    }
   
    for(std::size_t i=0 ; i < NUMTHREADS ; i++)
    {
        pthread_join(tids[i], &partialSol);
        pi +=  *static_cast<double*>(partialSol); 
        delete static_cast<double*>(partialSol);
    }
    
    pi = 4.0*(pi/NUMITERATIONS);
    
    clock_gettime(CLOCK_REALTIME, &endTime);
    
    double runtime = (endTime.tv_sec-startTime.tv_sec)+(endTime.tv_nsec-startTime.tv_nsec)/1e9;
    
    std::cout << std::fixed;
    std::cout << std::setprecision(20);
    
    std::cout << "The value of Pi is approximately " << pi << "." << std::endl;
    std::cout << "The program took " << runtime << " sec." << std::endl;
   
    return 0;
}
