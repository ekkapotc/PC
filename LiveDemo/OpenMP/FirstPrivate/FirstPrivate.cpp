#include <omp.h>
#include <iostream>

int main(int argc,char ** argv){
    
   int n = 4;
   int vlen = 20;
   int a[vlen];

   for(int i=0;i<vlen;i++) a[i] = -i-1;

   int indx = 4;

   #pragma omp parallel default(none) firstprivate(indx) shared(n,a)
   {
      int tid = omp_get_thread_num();
      indx += n*tid;

      for(int i=indx ; i<indx+n ; i++)
	      a[i] = tid + i;
   }/*---End of parallel region---*/

   std::cout << "After the parallel region:" << std::endl;
   
   for(int i=0;i<vlen;i++)
	   std::cout << "a["<<i<<"] = " << a[i] << std::endl;

   return 0;
}
