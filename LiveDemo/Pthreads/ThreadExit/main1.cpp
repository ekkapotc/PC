
#include <pthread.h>
#include <iostream>

#define NUMTHREADS 4

void * start(void * arg){
  std::cout << "Thread :" << *reinterpret_cast<int*>(arg) << std::endl;
  return arg;
  //pthread_exit(arg);
}

int main(int argc , char ** argv){
  int vals[4];
  pthread_t tids[4];
  void *retval;

  for (auto i=0; i < NUMTHREADS; i++) {
    vals[i] = i;
    pthread_create(&tids[i], NULL, start, &vals[i]);
  }

  for(auto i = 0; i < NUMTHREADS; i++) {
    std::cout << "Main Thread:  Joining with Thread " << i << std::endl;
    
    pthread_join(tids[i], &retval);
    
    std::cout << "Main Thread:  Successfuly joined with Thread " << i << "with Return Value " << *static_cast<int*>(retval)<<   std::endl;
  }
  
  return 0;
}
