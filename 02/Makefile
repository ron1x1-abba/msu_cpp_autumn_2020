all: test_one test_two test_three test_four test_five
test: test_one test_two test_three test_four test_five
	./test_one < input-1
	./test_two < input-1
	./test_three < input-1
	./test_four < input-1
	./test_five < input-1

Parser.o:
	g++ -Wall -g -std=c++17 -c -fsanitize=address,undefined Parser.cpp
test_one: Parser.o
	g++ -Wall -g  -std=c++17 -fsanitize=address,undefined test_one.cpp Parser.o -o test_one
test_two: Parser.o
	g++ -Wall -g  -std=c++17 -fsanitize=address,undefined test_two.cpp Parser.o -o test_two
test_three: Parser.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test_three.cpp Parser.o -o test_three
test_four: Parser.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test_four.cpp Parser.o -o test_four
test_five: Parser.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test_five.cpp Parser.o -o test_five
clean:
	rm  *.o test_one test_two test_three test_four test_five