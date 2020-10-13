#include "Allocator.hpp"

int main()
{
	Allocator a;
	a.makeAllocator(1024);
	char* ptr1 = a.alloc(45);
	char* ptr2 = a.alloc(10);
	if ((ptr2 - ptr1) == 45)
		std::cout << "Numerous allocation works fine!" << std::endl;
	else
		std::cout << "Numerous allocation doesn't work!" << std::endl;
	return 0;
}
