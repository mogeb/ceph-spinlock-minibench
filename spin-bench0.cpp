#include "Spinlock.h"

#include <thread>

void spinlock_bench(long n)
{
 long foo = 0;

 std::atomic_flag f { false };
 ceph::simple_spin_lock(f);
 for(; n; --n)
  foo++;
 ceph::simple_spin_unlock(f);
}

void spinlock_bench2(long n)
{
 long foo = 0;

 ceph::Spinlock l;
 ceph::ceph_spin_lock(l);
 for(; n; --n)
  foo++;
 ceph::ceph_spin_unlock(l);
}

void spinlock_bench3(long n)
{
 // Start two threads; one thread increments, one thread decrements:

 long foo = 0;

 ceph::Spinlock l;

 auto inc_thread = [&](long n) {
                    for(; n; --n)
                     l.lock(), foo++, l.unlock();
                   }; 

 auto dec_thread = [&](long n) {
                    for(; n; --n)
                     l.lock(), foo--, l.unlock();
                   }; 

 std::thread t0(inc_thread, n); 
 std::thread t1(dec_thread, n); 

 t0.join(), t1.join();
}
