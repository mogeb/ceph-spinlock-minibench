
all:
	g++-6 -std=c++11 -Wall -Wextra -O3 -o spin-bench0 spin-bench0.cpp
	g++-6 -std=c++11 -Wall -Wextra -O3 -o spin-bench1 spin-bench1.cpp simple_spin.cc -pthread
