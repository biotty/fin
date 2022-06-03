
CFLAGS = -std=c++2a -I.

.PHONY:
verify: test/fm_test
	test/fm_test

test/fm_test: test/fm_test.cpp fm.o
	$(CXX) $(CFLAGS) -o $@ test/fm_test.cpp fm.o

fm.o: fm.cpp fm.hpp
	$(CXX) $(CFLAGS) -c fm.cpp

.PHONY:
clean:
	rm -f fm.o

.PHONY:
sweep: clean
	rm -f test/fm_test
