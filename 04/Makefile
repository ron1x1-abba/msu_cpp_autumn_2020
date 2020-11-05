all:
test: test_all
	./test_all
BigInt.o:
	g++ -Wall -g -std=c++17 -c -fsanitize=address,undefined BigInt.cpp
test_all: BigInt.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test.cpp BigInt.o -o test_all
clean:
	rm *.o test_all
