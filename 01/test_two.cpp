#include "Allocator.hpp"

int main() {
	Allocator a;
	a.makeAllocator(2048);
	char* pointer = a.alloc(5000);
	if (pointer)
		std::cout << "OK Size is controlled well!" << std::endl;
	else
		std::cout << "Bad! Smth wrong with size controll!" << std::endl;
	return 0;
}
