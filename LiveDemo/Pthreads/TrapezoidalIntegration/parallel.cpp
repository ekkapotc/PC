#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

#define NUM_THREADS 4

typedef struct thrArgs{
    double a;
    double b;
    long n;
    long TID;
}thrArgs_t;

double f(double x)
{
  return 5.2*x*x+1.2*x+4.8;
}

void * parallelIntTrap(void * args){
    
  thrArgs_t * info = static_cast<thrArgs_t*>(args);
  
  long TID = info->TID;
  long n = info->n;
  double a = info->a;
  double b = info->b;
  double h = (b-a)/n;
  
  long startIndex =  TID*n/NUM_THREADS;
  long endIndex   =  ((TID+1)*n/NUM_THREADS-1);
  endIndex  =   endIndex <n ?  endIndex : n-1;
  
  double * localSum = new double();
  
  if(TID==NUM_THREADS-1){
    *localSum -= (f(a)+f(b))/2.0;
  }
  
  for(long i=startIndex;i<=endIndex;i++){
    *localSum += f(a+(i*h));
  }
  
  *localSum = (*localSum)*h;

  pthread_exit(static_cast<void*>(localSum));  
}

int main(int argc,char**argv)
{
  long n;
  double a,b;

  std::cout << std::setprecision(12);

  std::cout << "Enter the Lower Limit (a) :";
  std::cin >> a;
  std::cout << "Enter the Upper Limit (b) :";
  std::cin >> b;
  std::cout << "Enter the Number of Trapezoids (n) :";
  std::cin >> n;
    
  struct timespec startTime, endTime;

  clock_gettime(CLOCK_REALTIME, &startTime);
  
  pthread_t tids[NUM_THREADS];
  thrArgs_t args[NUM_THREADS];
  
  pthread_mutex_t mutex;
  
  pthread_mutex_init(&mutex, NULL);
  
  for( long TID=0; TID < NUM_THREADS; TID++ ){
    args[TID].a = a;
    args[TID].b = b;
    args[TID].n = n;
    args[TID].TID = TID;
    pthread_create( &tids[TID],NULL,&parallelIntTrap, static_cast<void*>(&args[TID]) );
  }

  void * localSum;
  double globalSum = 0.0;
  
  for(long TID=0;TID<NUM_THREADS;TID++){
    pthread_join(tids[TID],&localSum);
    globalSum +=  *static_cast<double*>(localSum); 
    delete (static_cast<double*>(localSum));
  }

  pthread_mutex_destroy(&mutex);
  
  clock_gettime(CLOCK_REALTIME, &endTime);
    
  double runtime = (endTime.tv_sec-startTime.tv_sec)+(endTime.tv_nsec-startTime.tv_nsec)/1e9;
  
  std::cout << globalSum << std::endl;
  std::cout << "The program took " << runtime << " sec." << std::endl;

  return 0;
}
