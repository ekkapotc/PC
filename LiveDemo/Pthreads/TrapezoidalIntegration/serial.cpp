#include <iostream>
#include <iomanip>
#include <cstdlib>

double f(double x)
{
  return 5.2*x*x+1.2*x+4.8;
}

double serialTrapInt(double a , double b , double h , long n)
{

  
  double integral = (f(a)+f(b))/2.0;

  for(long i=1;i<=n-1;i++){
    integral+=f(a+(i*h));
  }
  
  integral = h*integral;

  return integral;

}


int main(int argc , char ** argv){
    
    long n;
    double a,b;

    std::cout <<  std::setprecision(12);

    std::cout << "Enter the Lower Limit (a) :";
    std::cin >> a;
    std::cout << "Enter the Upper Limit (b) :";
    std::cin >> b;
    std::cout << "Enter the Number of Trapezoids (n) :";
    std::cin >> n;
    
    struct timespec startTime, endTime;
    clock_gettime(CLOCK_REALTIME, &startTime);
    
    double h = (b-a)/n;
    
    double solution = serialTrapInt(a,b,h,n);
    
    clock_gettime(CLOCK_REALTIME, &endTime);

    double runtime = (endTime.tv_sec-startTime.tv_sec)+(endTime.tv_nsec-startTime.tv_nsec)/1e9;
    std::cout << solution << std::endl;
    std::cout << "The program took " << runtime << " sec." << std::endl;
    
    return 0;
}
