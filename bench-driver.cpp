#include "minibench.hpp"

#include <iostream>

void spinlock_bench(long n);
void spinlock_bench2(long n);
void spinlock_bench3(long n);

int main(int argc, char *argv[])
try
{
 unsigned long N = 1000000000,
               n = 100000,
               m = 1000;

 if(2 <= argc)
  N = std::stoul(argv[1]);

 if(3 <= argc)
  n = std::stoul(argv[2]);

 if(4 <= argc)
  m = std::stoul(argv[3]);

 if(not ((N > n) && (n > m)))
  std::cout << "Warning: test run sizes may be mismatched.\n";

 std::cout << "Runs of: " << N << "L, " << n << "s, " << m << 'm' << std::endl;

 std::cout << ceph::minibench::bench("ceph::simple_spin_lock", spinlock_bench, N,  n, m) << std::endl;
 std::cout << ceph::minibench::bench("ceph::Spinlock", spinlock_bench2, N, n, m) << std::endl;
 std::cout << ceph::minibench::bench("ceph::Spinlock-threads", spinlock_bench3, N, n, m, ceph::minibench::run_type::miniscule_yet_mighty) << std::endl;
}
catch(std::exception& e)
{
 std::cout << "oops: " << e.what() << '\n';
}
