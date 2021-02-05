#include <iostream>
#include <unistd.h> //for the sleep() function
#include <pthread.h>
#define NUMTHREADS 8

void * hello(void* arg){
   std::cout << "Thread " << reinterpret_cast<size_t>(arg) << " : Hello World !"  << std::endl;
}

int main(int argc , char ** argv){
   pthread_t tids[NUMTHREADS];

   for(auto i=0 ; i<NUMTHREADS ; i++){
   	pthread_create(&tids[i],NULL , &hello ,  reinterpret_cast<void*>(i) );
   }


   std::cout << "Hello World from the main thread !" << std::endl;

   for(auto i=0 ; i<NUMTHREADS ; i++){
	 std::cout << "Main Thread: Joining with Thread " << i << std::endl;
         pthread_join(tids[i],NULL);
	 std::cout << "Main Thread: Succesfully joined with Thread " << i << std::endl; 
   }

   return 0;
}


