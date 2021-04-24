#include <omp.h>
#include <iostream>

int a;
double x;
 
#pragma omp threadprivate(a, x)

int main(int argc, char ** argv)
{   
    int  b, i, tid;
    double x;
 
   /*turn off dynamic threads mechanism*/
   omp_set_dynamic(0);
 
   std::cout << "The 1st Parallel Region:" << std::endl;
   
   #pragma omp parallel private(b,tid)
   {
        tid = omp_get_thread_num();
        a = tid;
        b = tid;
        x = 1.2* tid + 2.5;
        
        #pragma omp critical
        std::cout << "Thread " << tid << " :   a = " << a << " , b = " << b << " , x = " << x << std::endl;
        
   }/*--- End of Parallel Region ---*/
 
  
 
   std::cout << "The 2nd Parallel Region:" << std::endl;
   
   #pragma omp parallel private(tid)
   {
        tid = omp_get_thread_num();
        
        #pragma omp critical
        std::cout << "Thread " << tid << " :   a = " << a << " , b = " << b << " , x = " << x << std::endl;
        
   }/*--- End of Parallel Region ---*/
   
   return 0;

 }
