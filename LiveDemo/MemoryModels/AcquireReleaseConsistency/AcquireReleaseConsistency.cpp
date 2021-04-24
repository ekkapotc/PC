#include <thread>
#include <atomic>
#include <iostream>
#include <cassert>

#define MAX_ITERS 1000

std::atomic<bool> x,y;

void f()
{
    x.store(true,std::memory_order_relaxed);
    y.store(true,std::memory_order_release);
}   

void g()
{
    while(!y.load(std::memory_order_acquire)){};
    
    assert(x.load(std::memory_order_relaxed));
}

void h()
{
    x.store(true,std::memory_order_release);
}

void i()
{
    y.store(true,std::memory_order_release);
}

void j()
{
   while(!x.load(std::memory_order_acquire)){}

   if(y.load(std::memory_order_acquire)){
   	std::cout << "x == true then also y == true \n";
   }
}

void k()
{
   while(!y.load(std::memory_order_release)){}

   if(x.load(std::memory_order_acquire)){
        std::cout << "y == true then also x == true \n";
   }
}

int main(int arc , char ** argv)
{
    std::size_t c = MAX_ITERS;
    
    /*--- Test I ---*/
   
    std::cout << "Test I begins...\n";

    while(c>0)
    {
	std::cout << "-----Iteration------\n";

        x = false;
        y = false;
        
        std::thread t1{f};
        std::thread t2{g};
    
        t1.join();
        t2.join();
        
        c--;
    }


    /*--- Test II ---*/
    
    std::cout << "Test II begins...\n";

    c = MAX_ITERS;

    while(c>0)
    {
       std::cout << "------Iteration------\n";

       x = false;
       y = false;

       std::thread t1{h};
       std::thread t2{i};
       std::thread t3{j};
       std::thread t4{k};

       t1.join();
       t2.join();
       t3.join();
       t4.join();

       c--;
    }

    return 0;
}
