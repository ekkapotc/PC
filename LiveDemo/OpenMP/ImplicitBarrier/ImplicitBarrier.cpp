#include <omp.h>
#include <iostream>

int main(int argc,char ** argv){
 
    int i,n=128;
    double a[n],b[n];
    
    #pragma omp parlllel default(none) shared(n,a,b), private(i)
    {
        #pragma omp for
        for(i=0 ; i<n ; i++)
        {
            a[i] = static_cast<double>(i);
        }/*---Implicit barrier---*/
        
        #pragma omp for
        for(i=0 ; i<n ; i++)
        {
            b[i] = a[i]*static_cast<double>(i);
        }/*---Implicit barrier---*/
    }/*---End of parallel region---*/
    
    return 0;
}
