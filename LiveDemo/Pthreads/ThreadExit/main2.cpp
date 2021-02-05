#include <unistd.h> //for the sleep() function
#include <pthread.h>
#include <iostream>

#define NUMTHREADS 8

void * start(void * arg){
  sleep(2);
  int tid = *reinterpret_cast<int*>(arg);
  std::cout << "Thread :" << tid << std::endl;
  pthread_exit(arg);
}

int main(int argc , char ** argv){
  int vals[4];
  pthread_t tids[4];
  void *retval;

  for (auto i = 0; i < NUMTHREADS; i++) {
    vals[i] = i;
    pthread_create(&tids[i], NULL, start, &vals[i]);
  }

  /*for(auto i = 0; i < NUMTHREADS; i++) {
    std::cout << "Main Thread:  Joining with Thread " << i << std::endl;
    
    pthread_join(tids[i], &retval);
    
    std::cout << "Main Thread:  Successfuly joined with Thread " << i << " whose  Return Value is " <<  *static_cast<int*>(retval) << std::endl;
  }*/
  
  pthread_exit(0);
}
