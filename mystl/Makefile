
test_algorithm : test/test_algorithm.cpp mystl/algorithm.hpp
	g++ -std=c++17 -I. -fsanitize=address -g -Wall $< -o $@

.PHONY: test
test : test_algorithm
	./test_algorithm
