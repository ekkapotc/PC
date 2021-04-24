#include <iostream>
#include <pthread.h>
#include <unistd.h>

void * func(void * arg){
   sleep(3);
   int * buffPtr = static_cast<int*>(arg);
   *buffPtr = 99;
   pthread_exit(0);
}

int main(){
   int buff;
   pthread_t tid;
   pthread_create(&tid,NULL,&func,&buff);
   pthread_exit(0);
}


