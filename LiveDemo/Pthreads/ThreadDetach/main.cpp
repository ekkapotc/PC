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
    
    pthread_attr_t attr;
    
    if(pthread_attr_init(&attr)){//initialize with default attributes
        std::cerr << "Main Thread: failed to initialize the attributes object..." << std::endl;   
    }
    
    if(pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED)){
        std::cerr << "Main Thread: failed to intialize the attributes object with PTHREAD_CREATE_DETACHED..." << std::endl; 
    }
    
    
    pthread_create(&cid,&attr,&consumer,NULL);
    
    for(auto i=0; i<NUMPRODUCERS ;i++){
        int id = i;
        pthread_create(&pids[i],&attr,&producer, &id);
    }
    
    if(pthread_attr_destroy(&attr)){
        std::cerr << "Main Thread: failed to destroy the attributes object..." << std::endl; 
    }
    
    
    pthread_exit(0);
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
            
            i--;
            
            if(pthread_mutex_unlock(&mtx)){
                std::cerr << "Consumer failed to release the mutex..." << std::endl;  
            }
            
            sleep(1);
            continue;
        }
        
        if(pthread_mutex_unlock(&mtx)){
          std::cerr << "Consumer failed to release the mutex..." << std::endl;  
        }
        
        sleep(1);
    }
}
