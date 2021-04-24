#include <omp.h>
#include <iostream>

#define N 1024

int main(int argc,char** argv){
  
  double a[1024];

  for(int i=0; i<N;i++)
	a[i] = static_cast<double>(i*i);

  #pragma omp parallel shared(a)
  {
        #pragma omp for 
        for(int i=0;i<N;i++)
        {
            a[i] += static_cast<double>(i);
      
        }/*--- End of parallel for ---*/
  }
  
  return 0;
}
