#include <iostream>
#include <unistd.h> //for the sleep() function
#include <pthread.h>

#define NUMPRODUCERS 8

void * producer(void *);

void * consumer(void *);

int avail = 0;// a shared variable 

pthread_mutex_t * mtx;

int main(int argc , char** argv){
    
    pthread_t cid;
    pthread_t pids[NUMPRODUCERS];
    
    mtx = new pthread_mutex_t();
    
    pthread_mutex_init(mtx,NULL);//initialize with default attributes
    
    pthread_create(&cid,NULL,&consumer,NULL);
    
    for(auto i=0; i<NUMPRODUCERS ;i++){
        int id = i;
        pthread_create(&pids[i],NULL,&producer, &id);
    }
    
    
    
    for(auto i=0; i<NUMPRODUCERS;i++){
        pthread_join(pids[i],NULL);
    }
    
    pthread_join(cid,NULL);
    
    pthread_mutex_destroy(mtx);//destroy the mutex

    delete mtx;//free up the memory occupied by the mutex
    
    return 0;
}

void * producer(void * arg){
    
   sleep(1);
    
   if(pthread_mutex_lock(mtx)){
      std::cerr << "Producer " << *static_cast<int*>(arg) << " failed to acquire the mutex..." << std::endl;   
   }
   
   avail++;

   if(pthread_mutex_unlock(mtx)){
      std::cerr << "Producer " <<  *static_cast<int*>(arg)<< " failed to release the mutex..." << std::endl;   
   }

}

void * consumer(void * arg){
   for(int i=0;i<NUMPRODUCERS;i++){
       
        if(pthread_mutex_lock(mtx)){
           std::cerr << "Consumer failed to acquire the mutex..." << std::endl;   
        }
   
        if(avail>0){
            avail--;//consume one unit of resource
            std::cout << "Consumer saw " << avail+1 << " unit(s) of resource and consumed one unit of resource..." << std::endl;   
        }else{
            
            i--;
            
            if(pthread_mutex_unlock(mtx)){
                std::cerr << "Consumer failed to release the mutex..." << std::endl;  
            }
            
            sleep(1);
            continue;
        }
        
        if(pthread_mutex_unlock(mtx)){
          std::cerr << "Consumer failed to release the mutex..." << std::endl;  
        }
        
        sleep(1);
    }
}
