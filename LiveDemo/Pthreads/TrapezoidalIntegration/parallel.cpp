#include <pthread.h>
#include <stdio.h>
#include <iostream>

#define NUM_THREADS 4

typedef struct thrArgs{
    double a;
    double b;
    long n;
    long TID;
}thrArgs_t;

double f(double x)
{
  return x*x;
}

void * parallelIntTrap(void * args){
    
  thrArgs_t * info = (thrArgs_t*) args;
  
  long TID = info->TID;
  long n = info->n;
  double a = info->a;
  double b = info->b;
  double h = (b-a)/n;
  
  long startIndex =  TID*n/NUM_THREADS;
  long endIndex  =   ((TID+1)*n/NUM_THREADS-1) <n ?  ((TID+1)*n/NUM_THREADS-1) : n-1;
  
  //printf("TID %ld , start %ld , end %ld\n",TID, startIndex, endIndex);
  
  double * localSum = new double();
  
  if(TID==0){
    *localSum += (f(a)+f(b))/2.0;
  }

  for(long i=startIndex;i<=endIndex;i++){
    *localSum += f(a+(i*h));
  }
  
  *localSum = (*localSum)*h;

  pthread_exit((void *)localSum);  
}

int main(int argc,char**argv)
{
  long n;
  double a,b;
    
  std::cout << "Enter the Lower Limit (a) :";
  std::cin >> a;
  std::cout << "Enter the Upper Limit (b) :";
  std::cin >> b;
  std::cout << "Enter the Number of Trapezoids (n) :";
  std::cin >> n;
    
  //double h = (b-a)/n;
  pthread_t tids[NUM_THREADS];
  thrArgs_t args[NUM_THREADS];
  
  pthread_mutex_t mutex;
  
  pthread_mutex_init(&mutex, NULL);
  
  for( long TID=0; TID < NUM_THREADS; TID++ ){
    args[TID].a = a;
    args[TID].b = b;
    args[TID].n = n;
    args[TID].TID = TID;
    pthread_create( &tids[TID],NULL,&parallelIntTrap, (void*)&args[TID] );
  }

  void * localSum;
  double globalSum = 0.0;
  
  for(long TID=0;TID<NUM_THREADS;TID++){
    pthread_join(tids[TID],&localSum);
    globalSum +=  *(double*)localSum; 
    delete ((double*)localSum);
  }

  pthread_mutex_destroy(&mutex);
  
  std::cout << globalSum << std::endl;

  return 0;
}
