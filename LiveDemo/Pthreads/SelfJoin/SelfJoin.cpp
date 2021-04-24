#include <iostream>
#include <pthread.h>
#include <cstring>

int main(int argc,char** argv){
  	int rtn{0};
	pthread_t tid = pthread_self();


	if(!pthread_equal(tid,pthread_self()))
        	
	   rtn =  pthread_join(tid,NULL);

        if(rtn)

	   std::cout << strerror(rtn) << std::endl;
	
	return 0;
}
