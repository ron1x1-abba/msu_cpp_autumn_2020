#include "Allocator.hpp"

int main() {
	Allocator a;
	a.makeAllocator(1024);
	char* ptr1 = a.alloc(5);
	a.reset();
	char* ptr2 = a.alloc(5);
	if (ptr1 == ptr2)
		std::cout << "Reset works fine!" << std::endl;
	else
		std::cout << "Reset works bad!" << std::endl;
	return 0;
}