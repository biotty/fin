
CFLAGS = -std=c++17 -I.

.PHONY:
verify: test/fom_test
	test/fom_test

test/fom_test: test/fom_test.cpp fom.o
	$(CXX) $(CFLAGS) -o $@ test/fom_test.cpp fom.o

fom.o: fom.cpp fom.hpp
	$(CXX) $(CFLAGS) -c fom.cpp

.PHONY:
clean:
	rm -f fom.o

.PHONY:
sweep: clean
	rm -f test/fom_test
