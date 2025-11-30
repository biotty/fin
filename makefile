CXXFLAGS = -std=c++17 -I.

.PHONY:
verify: test/fom_test
	test/fom_test

test/fom_test: test/fom_test.cpp fom.o
	$(CXX) $(CXXFLAGS) -o $@ test/fom_test.cpp fom.o -lgtest -lgtest_main

fom.o: fom.cpp fom.hpp
	$(CXX) $(CXXFLAGS) -c fom.cpp

.PHONY:
clean:
	rm -f fom.o

.PHONY:
sweep: clean
	rm -f test/fom_test
