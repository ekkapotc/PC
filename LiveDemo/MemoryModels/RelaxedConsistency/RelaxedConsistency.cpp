#include <thread>
#include <atomic>
#include <iostream>
#include <cassert>

#define MAX_ITERS 1000000

std::atomic<bool> x,y;

void f()
{
    x.store(true,std::memory_order_relaxed);
    y.store(true,std::memory_order_relaxed);
}

void g()
{
    while(!y.load(std::memory_order_relaxed)){};
    
    assert(x.load(std::memory_order_relaxed));
    
}

int main(int arc , char ** argv)
{
    std::size_t c = MAX_ITERS;
    
    while(c>0)
    {
        x = false;
        y = false;
        
        std::thread t1{f};
        std::thread t2{g};
    
        t1.join();
        t2.join();
        
        c--;
    }
    
    return 0;
}
