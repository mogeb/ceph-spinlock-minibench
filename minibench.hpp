#ifndef MINIBENCH_HPP_20170413 
 #define MINIBENCH_HPP_20170413

#include <chrono>
#include <string>
#include <sstream>

namespace ceph { namespace minibench {

template <typename FnT>
std::string bench(FnT f, unsigned long N, const std::string& name)
{
 using namespace std::chrono;

 std::ostringstream os;
 os << name << ":\n";
 
 time_point<high_resolution_clock> start { high_resolution_clock::now() };

 while(--N)
  f();

 time_point<high_resolution_clock> end { high_resolution_clock::now() };

 auto elapsed = end - start;

 os << elapsed.count();
 return os.str();
}

}} // namespace ceph::minibench 

#endif
