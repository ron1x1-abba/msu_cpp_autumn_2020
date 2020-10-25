all:
test: test_one test_two test_three test_four test_five test_six
	./test_one
	./test_two
	./test_three
	./test_four
	./test_five
	./test_six
Matrix.o:
	g++ -Wall -g -std=c++17 -c -fsanitize=address,undefined Matrix.cpp
test_one: Matrix.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test_one.cpp Matrix.o -o test_one
test_two: Matrix.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test_two.cpp Matrix.o -o test_two
test_three: Matrix.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test_three.cpp Matrix.o -o test_three
test_four: Matrix.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test_four.cpp Matrix.o -o test_four
test_five: Matrix.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test_five.cpp Matrix.o -o test_five
test_six: Matrix.o
	g++ -Wall -g -std=c++17 -fsanitize=address,undefined test_six.cpp Matrix.o -o test_six
clean:
	rm *.o test_one test_two test_three test_four test_five test_six