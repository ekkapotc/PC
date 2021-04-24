#include <iostream>
#include <pthread.h>
#include <cstring>

void * bullet_proof(void *){
   pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);


}

int main(int argc,char** argv){
   int buff;
   pthread_t tid;
  

   pthread_create(&tid,NULL,&bullet_proof,NULL);

   int rtn = pthread_join(tid, NULL);
   
   if(rtn)
     std::cout << strerror(rtn) << std::endl;

   return 0;
}

