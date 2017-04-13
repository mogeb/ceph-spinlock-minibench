
#include "ORIG-simple_spin.h"
#include "ORIG-Spinlock.h"

#include "minibench.hpp"

#include <thread>
#include <iostream>

namespace {

unsigned long foo;

} // namespace

void spinlock_bench(long n)
{
 simple_spinlock_t l { SIMPLE_SPINLOCK_INITIALIZER };

 simple_spin_lock(&l);
 for(; n; --n)
  foo++;
 simple_spin_unlock(&l);
}

void spinlock_bench2(long n)
{
 Spinlock l;

 l.lock();
 for(; n; --n)
  foo++;
 l.unlock();
}

void spinlock_bench3(long n)
{
 // Start two threads; one thread increments, one thread decrements:

 long foo = 0;

 Spinlock l;

 auto inc_thread = [&](long n) {
                    for(; n; --n)
                     l.lock(), foo++, l.unlock();
                   }; 

 auto dec_thread = [&](long n) {
                    for(; n; --n)
                     l.lock(), foo++, l.unlock();
                   }; 

 std::thread t0(inc_thread, n); 
 std::thread t1(dec_thread, n); 

 t0.join(), t1.join();
}

