#include <omp.h>
#include <iostream>

int main(int argc,char** argv){

  int n = 5;
  int a;

  #pragma omp parallel for shared(n) lastprivate(a)
  for(int i=0;i<n;i++)
  {
	a = i+1;
	
  }/*---End of parallel for---*/
  
  std::cout << "After the parallel region, a = " << a << std::endl;
  	
  return 0;
}
