#include <omp.h>
#include <iostream>

#define m 2
#define n 100000000

bool equal(double * A , double * B, int k)
{
    for(int i=0;i<k;i++)
    {
       if(A[i]!=B[i]) return false;   
    }
    
    return true;
}

int main(int argc , char ** argv)
{
    double * A, * B, * C;
   
    A = new double[m*n];
    B = new double[m*n];
    C = new double[m*n];
    
    //serial 
    for(int i=0;i<m;i++)
       for(int j=0;j<n;j++)
           A[i*n+j] = i+j+1;
       
    //serial with loop nest elimination
    for(int k=0;k<m*n;k++)
    {
       int i = (k/n) % m;
       int j = k % n;
       B[i*n+j] = i+j+1;
    }
       
    if(equal(A,B,m*n))
       std::cout << "A = B" << std::endl;
    else
       std::cout << "A != B " << std::endl;
   
    //parallel with collapse clause
    #pragma omp parallel for collapse(2) num_threads(omp_get_num_procs())
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            C[i*n+j] = i+j+1;
    
        
    if(equal(A,C,m*n))
       std::cout << "A = C" << std::endl;
    else
       std::cout << "A != C " << std::endl;
    
    delete [] A;
    delete [] B;
    delete [] C;
    
    return 0;
}
