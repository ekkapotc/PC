#include <omp.h>

int main(){
    
    int a, b ,c;
    
    #pragma omp parallel default(none) shared(a,b,c)
    {
        int i = a+b*c;    
    }
    
    return 0;   
}
