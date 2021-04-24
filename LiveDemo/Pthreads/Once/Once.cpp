#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <pthread.h>

#define  NUM_THREADS   4

static pthread_once_t welcome_once_block = PTHREAD_ONCE_INIT;

static bool seenFirst = false;

void welcome(void)
{
	printf("welcome: Welcome\n");
}

void *identify_yourself(void *arg)
{
    int *pid=(int *)arg;
	int rtn;

	if ((rtn = pthread_once(&welcome_once_block,welcome)) != 0)
    {
		fprintf(stderr, "pthread_once failed with %d",rtn);
		pthread_exit((void *)NULL);
	}
    
	printf("identify_yourself: Hi, I'm thread # %d\n",*pid);
        return(NULL);
}

int main(int argc,char * argv[])
{
	int             *id_arg, thread_num, rtn;
	pthread_t       threads[NUM_THREADS];

	id_arg = (int *)malloc(NUM_THREADS*sizeof(int));

	for (thread_num = 0; thread_num < NUM_THREADS; (thread_num)++) {

		id_arg[thread_num] = thread_num;

		if (( rtn = pthread_create(&threads[thread_num], 
					   NULL,
					   identify_yourself,
					   (void *) &(id_arg[thread_num]))) 
		    != 0) {
		  fprintf(stderr, "pthread_create failed with %d",rtn);
		  exit(1);
		}
	} 	

	for (thread_num = 0; thread_num < NUM_THREADS; thread_num++) {
	  pthread_join(threads[thread_num], NULL);
	  printf("main: joined to thread %d\n", thread_num);
	}
	printf("main: Goodbye\n");
}
