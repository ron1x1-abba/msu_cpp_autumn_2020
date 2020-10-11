#pragma once
#include <iostream>
#include <cstdlib>

class Allocator {
	char* startPointer = nullptr;
	size_t curPosition = 0;
	size_t maxPossibleSize = 0;
public:
	~Allocator();
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
};