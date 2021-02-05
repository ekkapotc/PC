#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#define WITHDRAW                70
#define FILL                    50
#define FILL_FREQUENCY          5
#define NUM_ATMS                3
#define NUM_CUSTOMERS           5

pthread_mutex_t mutex;
pthread_cond_t enough;

int cash = 0;//skeleton


void* fill(void* arg){
    for (int i = 0; i < FILL_FREQUENCY; i++){
        
        /**TO-DO: implement the fill() function for each ATM cash filling thread***/
        
        /*
         * Assume that 
         * 
         * 1) each ATM cash filling thread fills cash worth "FILL" bahts at a time every 1 hour.
         * 
         * 2) each ATM has unlimited storage for cash.
         */
        
        sleep(1);
    }
}

void* withdraw(void* arg){
    /**TO-DO: implement the withdraw() function for each customer thread***/
    
    /*
     *Assume that each customer withdraws cash worth "WITHDRAW" bahts from an ATM.
     */
}

int main(int argc, char* argv[])
{
    pthread_t atms[NUM_ATMS];
    pthread_t customers[NUM_CUSTOMERS];
    
    
    pthread_mutex_init(&mutex, NULL);
    
    pthread_cond_init(&enough, NULL);
    
    
    /**TO-DO: create 3 ATM threads***/
    
    /**TO-DO: create 5 customer threads**/
   
    /**TO-DO: join the main thread with each thread***/
    
    pthread_mutex_destroy(&mutex);
    
    pthread_cond_destroy(&enough);
    
    return 0;
}
