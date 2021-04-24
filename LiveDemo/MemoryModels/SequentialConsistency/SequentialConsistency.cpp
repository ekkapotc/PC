#include <thread>
#include <atomic>
#include <iostream>
#include <cassert>

#define MAX_ITERS 100000

std::atomic<bool> x,y;
std::atomic<int> z;

void f()
{
    x.store(true,std::memory_order_seq_cst);
}

void g()
{
    y.store(true,std::memory_order_seq_cst);
}

void h()
{
    while(!x.load(std::memory_order_seq_cst)){}
    if(y.load(std::memory_order_seq_cst)) z++;
}

void i()
{
    while(!y.load(std::memory_order_seq_cst)){}
    if(x.load(std::memory_order_seq_cst)) z++;
}

int main(int argc , char ** argv)
{
    std::size_t c = MAX_ITERS; 
    
    while(c>0)
    {
    
        x = false;
        y = false;
        z = 0;
    
        std::thread t1{f};
        std::thread t2{g};
        std::thread t3{h};
        std::thread t4{i};
    
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    
        assert(z.load()!=0);
        
        c--;
    }
    
    return 0;
}
