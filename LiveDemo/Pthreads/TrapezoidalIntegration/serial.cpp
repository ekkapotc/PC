#include <iostream>


double f(double x)
{
  return x*x;
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
    
    std::cout << "Enter the Lower Limit (a) :";
    std::cin >> a;
    std::cout << "Enter the Upper Limit (b) :";
    std::cin >> b;
    std::cout << "Enter the Number of Trapezoids (n) :";
    std::cin >> n;
    
    double h = (b-a)/n;
    
    double integral = serialTrapInt(a,b,h,n);
    std::cout << integral << std::endl;
    
    return 0;
}
