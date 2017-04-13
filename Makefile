
all:
	g++-6 -std=c++11 -Wall -Wextra -O3 -o spin-bench0 spin-bench0.cpp bench-driver.cpp -pthread 
	g++-6 -std=c++11 -Wall -Wextra -O3 -o spin-bench1 spin-bench1.cpp bench-driver.cpp ORIG-simple_spin.cc -pthread
