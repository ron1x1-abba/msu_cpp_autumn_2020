Allocator.o:
	g++ -Wall -g -c -fsanitize=address,undefined Allocator.cpp
all: test_one test_two test_three test_four
test: test_one test_two test_three test_four
	./test_one
	./test_two
	./test_three
	./test_four
test_one: Allocator.o
	g++ -Wall -g -fsanitize=address,undefined Allocator.o test_one.cpp -o test_one
test_two: Allocator.o
	g++ -Wall -g -fsanitize=address,undefined Allocator.o test_two.cpp -o test_two
test_three: Allocator.o
	g++ -Wall -g -fsanitize=address,undefined Allocator.o test_three.cpp -o test_three
test_four: Allocator.o
	g++ -Wall -g -fsanitize=address,undefined Allocator.o test_four.cpp -o test_four
clean:
	-rm *.o test_one test_two test_three test_four
