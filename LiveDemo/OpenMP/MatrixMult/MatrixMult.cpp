#include <omp.h>
#include <cmath>
#include <iostream>

int main(int argc,char** argv)
{
    int n = 1024;

    double pi = 3.141592653589793;
  
    double ** a = new double*[n];
    double ** b = new double*[n];
    double ** c = new double*[n];
 
    std::cout << "\tThe number of processors available = " << omp_get_num_procs ( ) << std::endl;
    std::cout << "\tThe number of threads available    = " << omp_get_max_threads ( ) << std::endl;;
    std::cout << "\tThe matrix order N                 = " << n << std::endl;

    double s = 1.0 / sqrt ( ( double ) ( n ) );

    double wall_time = omp_get_wtime ( );

    #pragma omp parallel default(none) shared( a, b, c, n, pi, s ) 
    {
        #pragma omp for nowait 
        for(int i = 0; i < n; i++ )
        {
            a[i] = new double[n];
    
            for (int j = 0; j < n; j++ )
            {
                double angle = 2.0 * pi * i * j / ( double ) n;
                a[i][j] = s*(sin ( angle ) + cos ( angle ));
            }
        }

        #pragma omp for 
        for(int i = 0; i < n; i++ )
        {
            b[i] = new double[n];
    
            for(int j = 0; j < n; j++ )
            {
                b[i][j] = a[i][j];
            }
        }

        #pragma omp for  nowait
        for(int i = 0; i < n; i++ )
        {
            c[i] = new double[n];  
      
            for(int j = 0; j < n; j++ )
            {
                c[i][j] = 0.0;
            
                for(int k = 0; k < n; k++ )
                { 
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
                }
            }
        }
    }
    
    wall_time = omp_get_wtime ( ) - wall_time;

    std::cout << "\tElapsed seconds =  " <<  wall_time << std::endl;
  
    #pragma omp parallel for shared (a,b,c) schedule(dynamic)
    for(int i = 0; i < n; i++ )
    {
        delete [] a[i];
        delete [] b[i];
        delete [] c[i];
    }
    
    delete [] a;
    delete [] b;
    delete [] c;
    
    return 0;
}
