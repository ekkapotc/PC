#include <iostream>
#include <unistd.h> //for the sleep() function
#include <pthread.h>

#define NUMTHREADS 8

void * hello(void* arg){
   std::cout << "Hello World from a newly created thread with id : " << reinterpret_cast<size_t>(arg)  << std::endl;
}

int main(int argc , char ** argv){
   pthread_t tids[NUMTHREADS];

   for(auto i=0 ; i<NUMTHREADS ; i++){
   	pthread_create(&tids[i],NULL , &hello , reinterpret_cast<void*>(i) );
   }

   sleep(1);

   std::cout << "Hello World from the main thread !" << std::endl;

   return 0;
}


