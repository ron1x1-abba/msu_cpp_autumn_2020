#include "Allocator.hpp"

int main() {
	Allocator a;
	a.makeAllocator(2048);
	char* pointer = a.alloc(256);
	if (ponter) {
		std::cout << "OK! Allocator returned correct pointer!" << std::endl;
	}
	else
		std::cout << "Bad! Allocator returned incorrect pointer!" << std::endl;
	return 0;
}