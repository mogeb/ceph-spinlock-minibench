
#include "Spinlock.h"

#include "minibench.hpp"

#include <iostream>

void spinlock_bench()
{
 std::atomic_flag f { false };

 ceph::simple_spin_lock(f);
 ceph::simple_spin_unlock(f);
}

void spinlock_bench2()
{
 ceph::Spinlock l;

 ceph::ceph_spin_lock(l);
 ceph::ceph_spin_unlock(l);
}

int main(int argc, char *argv[])
try
{
 unsigned long N = 1000000000;

 if(2 == argc)
  N = std::stoul(argv[1]);

 std::cout << "Runs of: " << N << std::endl;

 std::cout << ceph::minibench::bench(spinlock_bench, N,  "ceph::simple_spin_lock (stdlib)") << std::endl;
 std::cout << ceph::minibench::bench(spinlock_bench2, N, "ceph::Spinlock (stdlib)") << std::endl;
}
catch(std::exception& e)
{
 std::cout << "oops: " << e.what() << '\n';
}
