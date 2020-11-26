all: test
test: test_all
	./test_all
test_all: 
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test.cpp -o test_all
clean:
	rm test_all
