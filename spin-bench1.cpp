
#include "simple_spin.h"
#include "ORIG-Spinlock.h"

#include "minibench.hpp"

#include <iostream>

void spinlock_bench()
{
 simple_spinlock_t l { SIMPLE_SPINLOCK_INITIALIZER };

 simple_spin_lock(&l);
 simple_spin_unlock(&l);
}

void spinlock_bench2()
{
 Spinlock l;

 l.lock();
 l.unlock();
}

int main(int argc, char *argv[])
try
{
 unsigned long N = 1000000000;

 if(2 == argc)
  N = std::stoul(argv[1]);

 std::cout << "Runs of: " << N << std::endl;

 std::cout << ceph::minibench::bench(spinlock_bench, N,  "ceph::simple_spin_lock (original)") << std::endl;
 std::cout << ceph::minibench::bench(spinlock_bench2, N, "ceph::Spinlock (original)") << std::endl;
}
catch(std::exception& e)
{
 std::cout << "oops: " << e.what() << '\n';
}
