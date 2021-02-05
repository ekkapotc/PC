#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>

#define NUMITERATIONS 1000000000  


int main(int argc, char *argv[])
{
    srand (time(NULL));
   
    double totalCount = 0;
    double totalHits = 0;
   
    struct timespec startTime, endTime;
    clock_gettime(CLOCK_REALTIME, &startTime);

    for(auto i=0 ; i<NUMITERATIONS ; i++)
    {
        double  x = (double) rand()/(double) RAND_MAX;
        double  y = (double) rand()/(double) RAND_MAX;
      
        double result = std::sqrt((x*x) + (y*y));
      
        if(result<.0){
            totalHits += 1;         //check if the generated value is inside a unit circle
        }
      
        totalCount += 1;
   }    
   
    clock_gettime(CLOCK_REALTIME, &endTime);

    double runtime = (endTime.tv_sec-startTime.tv_sec)+(endTime.tv_nsec-startTime.tv_nsec)/1e9;

    double pi = 4.0*totalHits/totalCount;
   
    std::cout << std::fixed;

    std::cout << std::setprecision(20);
    
    std::cout << "The value of Pi is approximately " << pi << "." << std::endl;
    std::cout << "The program took " << runtime << " sec." << std::endl;
   
   return 0;
}
