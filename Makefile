EXECUTABLE = test_stats

CXX = g++
CXXFLAGS = -Wall -Werror -pedantic --std=c++17 -g -fsanitize=address -fsanitize=undefined

SOURCES = $(wildcard *.cpp)

test_stats: test_stats.cpp
	$(CXX) $(CXXFLAGS) test_stats.cpp -o $@

stats_lib: stats_lib.cpp
	$(CXX) $(CXXFLAGS) stats_lib.cpp -o $@

clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE)_debug
	rm -vrf *.o *.exe *.dSYM

debug: CXXFLAGS += -g3 -DDEBUG
debug:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_debug