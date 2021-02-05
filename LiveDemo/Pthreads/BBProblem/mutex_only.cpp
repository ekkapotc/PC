#include <iostream>
#include <unistd.h> //for the sleep() function
#include <pthread.h>

#define NUMPRODUCERS 8

void * producer(void *);

void * consumer(void *);

int avail = 0;// a shared variable 

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;//initiallizng a statically allocated mutex with the macro

int main(int argc , char** argv){
    
    pthread_t cid;
    pthread_t pids[NUMPRODUCERS];
    
    pthread_create(&cid,NULL,&consumer,NULL);
    
    for(auto i=0; i<NUMPRODUCERS ;i++){
        int id = i;
        pthread_create(&pids[i],NULL,&producer, &id);
    }
    
    
    
    for(auto i=0; i<NUMPRODUCERS;i++){
        pthread_join(pids[i],NULL);
    }
    
    pthread_join(cid,NULL);
    
    return 0;
}

void * producer(void * arg){
    
   sleep(1);
    
   if(pthread_mutex_lock(&mtx)){
      std::cerr << "Producer " << *static_cast<int*>(arg) << " failed to acquire the mutex..." << std::endl;   
   }
   
   avail++;

   if(pthread_mutex_unlock(&mtx)){
      std::cerr << "Producer " <<  *static_cast<int*>(arg)<< " failed to release the mutex..." << std::endl;   
   }

}

void * consumer(void * arg){
   for(int i=0;i<NUMPRODUCERS;i++){
       
        if(pthread_mutex_lock(&mtx)){
           std::cerr << "Consumer failed to acquire the mutex..." << std::endl;   
        }
   
        if(avail>0){
            avail--;//consume one unit of resource
            std::cout << "Consumer saw " << avail+1 << " unit(s) of resource and consumed one unit of resource..." << std::endl;   
        }else{
            
            i--;//adjust the loop counter
            
            if(pthread_mutex_unlock(&mtx)){
                std::cerr << "Consumer failed to release the mutex..." << std::endl;  
            }
            
            sleep(1);
            continue;//skip the current iteration
        }
        
        if(pthread_mutex_unlock(&mtx)){
          std::cerr << "Consumer failed to release the mutex..." << std::endl;  
        }
        
        sleep(1);
    }
}
