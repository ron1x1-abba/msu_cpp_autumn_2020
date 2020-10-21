all: test_one test_two
test: test_one test_two
	./test_one < input > test_one_output
	./test_two < input > test_two_output
	echo "Check and compare two outputs to ensure that tests work well!"

Parser.o:
	g++ -Wall -g -c -fsanitize=address,undefined Parser.cpp
test_one: Parser.o
	g++ -Wall -g -fsanitize=address,undefined test_one.cpp Parser.o -o test_one
test_two: Parser.o
	g++ -Wall -g -fsanitize=address,undefined test_two.cpp Parser.o -o test_two
clean:
	rm test_one_output test_two_output *.o test_one test_two