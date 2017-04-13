#ifndef MINIBENCH_HPP_20170413 
 #define MINIBENCH_HPP_20170413

#include <limits>
#include <chrono>
#include <string>
#include <random>
#include <sstream>

namespace ceph { namespace minibench {

template <long N = std::numeric_limits<long>::max(), long M = 0>
long random_value()
{
 static std::random_device rd;
 static std::mt19937 e(rd());
 static std::uniform_int_distribution<long> d {M, N};

 return d(e);
}

enum class run_type {
 regular_flavor,
 small_is_beautiful,
 miniscule_yet_mighty
};

template <typename FnT>
std::string bench(const std::string& name, 
                  FnT f, 
                  const unsigned long N, const unsigned long n, const unsigned long m,
                  const run_type rt = run_type::regular_flavor)
{
 using namespace std::chrono;

 std::ostringstream os;
 os << name << ":\n";
 
 time_point<high_resolution_clock> start { high_resolution_clock::now() };

 unsigned long runs = 0;
 switch(rt)
 {
    case run_type::regular_flavor:          runs = N; break;
    case run_type::small_is_beautiful:      runs = n; break;
    case run_type::miniscule_yet_mighty:    runs = m; break;
 }

 while(--runs)
  f(n);

 time_point<high_resolution_clock> end { high_resolution_clock::now() };

 auto elapsed = end - start;

 os << elapsed.count();
 return os.str();
}

}} // namespace ceph::minibench 

#endif
