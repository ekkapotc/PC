#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#define WITHDRAW    70
#define FILL        50
#define FILLITERS   5

pthread_mutex_t mutex;

pthread_cond_t enough;

int cash = 0;

void* fill(void* arg){
    for (int i = 0; i < FILLITERS; i++){
        
        pthread_mutex_lock(&mutex);
        
        cash += FILL;
        
        std::cout << "Filled cash to " << cash  << std::endl;
        
        pthread_mutex_unlock(&mutex);
        
        pthread_cond_broadcast(&enough);
        
        sleep(1);
    }
}

void* withdraw(void* arg){
    
    pthread_mutex_lock(&mutex);
    
    while(cash<WITHDRAW)
    {
        std::cout << "Not enough cash..."  << std::endl;
        pthread_cond_wait(&enough, &mutex);
    }
    
    cash -= WITHDRAW;
    
    std::cout << "Withdrew " << WITHDRAW << " bahts." << std::endl;
    std::cout << "There is now " << cash << " bahts left." << std::endl;
    
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[])
{
    pthread_t tids[8];
    
    pthread_mutex_init(&mutex, NULL);
    
    pthread_cond_init(&enough, NULL);
    
    for (int i = 0; i < 8; i++) {
        if (i == 5 || i == 6 || i == 7) {
            if (pthread_create(&tids[i], NULL, &fill, NULL)){
                std::cerr << "Failed to create ATM Thread " << i-5 << std::endl;
            }
        }else
        {
            if(pthread_create(&tids[i], NULL, &withdraw, NULL)){
                std::cerr << "Failed to create Customer Thread " << i << std::endl;
            }
        }
    }

    for (int i = 0; i < 8; i++){
        if(pthread_join(tids[i], NULL)){
            std::cerr << "Failed to join Thread " << i << std::endl;
        }
    }
    
    pthread_mutex_destroy(&mutex);
    
    pthread_cond_destroy(&enough);
    
    return 0;
}
