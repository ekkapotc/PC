#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <pthread.h>

#define QUEUE_SIZE          5
#define MAX_PRODUCED        30

#define PRODUCER_CPU_TIME   25
#define PRODUCER_BLOCK_TIME 10
#define CONSUMER_CPU_TIME   25
#define CONSUMER_BLOCK_TIME 10

static pthread_mutex_t mutex;
static pthread_cond_t  notEmpty;
static pthread_cond_t  notFull;
static int totalProduced = 0, totalConsumed = 0;
static std::queue<int> q;

int memoryAccessArea[100000];


/**
 * 
 * simulate doing I/O by putting the calling into sleep
 * 
 */
void msleep(unsigned int milliSeconds)
{
  struct timespec req = {0}; /* init struct contents to zero */
  time_t          seconds;

  seconds        = (milliSeconds/1000);
  milliSeconds  = milliSeconds - (seconds * 1000);

  req.tv_sec  = seconds;
  req.tv_nsec = milliSeconds * 1000000L;

  while(nanosleep(&req, &req)==-1) {
    std::cout << "restless" << std::endl;
    continue;
  }

}


/*
 * 
 *simulate doing work and I/O 
 * 
 */
void doWork(int cpuIterations, int blockingTime)
{
 
 int val = 1;
 
 for (int i = 0; i<cpuIterations; i++){
//simulate doing work
    for(int j = 0; j<2000; j++) {
      val += i*memoryAccessArea[j];
    }
  }
  
  if (blockingTime>0){
//simulate doing I/O
    msleep(blockingTime);
  }
}



void * producer(void * arg)
{
    size_t tid = reinterpret_cast<size_t>(arg);
    
    while(1)
    {
        doWork(PRODUCER_CPU_TIME, PRODUCER_BLOCK_TIME);

        
        while (q.size()==QUEUE_SIZE && totalProduced != MAX_PRODUCED)
        {
            std::cout << "Pro " << tid << " : FULL" << std::endl;
        }


        if(totalProduced >= MAX_PRODUCED){
            break;
        }

    
        int itemProduced = totalProduced++;

        q.push(itemProduced);
        
        std::cout << "Pro " << tid << " : " << itemProduced << std::endl;
    }

    std::cout << "Pro " << tid << " : Exited" << std::endl;
    
    pthread_exit(0);
}

void * consumer(void * arg)
{
    
    size_t tid = reinterpret_cast<size_t>(arg);
    
    while(1)
    {
    
        while(q.empty() && totalConsumed!=MAX_PRODUCED){
            std::cout << "Con " << tid << " : EMPTY" << std::endl;
        }


        if(totalConsumed >= MAX_PRODUCED){
    
            break;
        }

   
        int itemConsumed = q.front();
        
        q.pop();
        
        std::cout << "Con " << tid << " : " << itemConsumed << std::endl;
        
        totalConsumed++;

        doWork(CONSUMER_CPU_TIME,CONSUMER_BLOCK_TIME);
    }

    std::cout << "Con " << tid << " : Exited" << std::endl;
    
    pthread_exit(0);
    
}

int main(int argc,char ** argv)
{
    if(argc!=3){
        std::cerr << "USAGE: PC <no_of_producers> <no_of_consumers>" << std::endl;
        exit(1);
    }
    
    int numPro = atoi(argv[1]);
    int numCon = atoi(argv[2]);
    
  
    pthread_mutex_init (&mutex, NULL);
    pthread_cond_init (&notFull, NULL);
    pthread_cond_init (&notEmpty, NULL);

    
    pthread_t * pros = new pthread_t[numPro];
    pthread_t * cons = new pthread_t[numCon];
    
    for(size_t i=0;i<numPro;i++)
        
        pthread_create(&pros[i],NULL,&producer,reinterpret_cast<void*>(i));
    
    
    for(size_t i=0;i<numCon;i++)
    
        pthread_create(&cons[i],NULL,&consumer,reinterpret_cast<void*>(i));
    
    
    for(size_t i=0; i<numPro; i++)
        
        pthread_join (pros[i], NULL);
    
    for(size_t i=0; i<numCon; i++)
        
        pthread_join (cons[i], NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&notFull);
    pthread_cond_destroy (&notEmpty);
    
    delete [] pros;
    delete [] cons;
    
    return 0;
}
