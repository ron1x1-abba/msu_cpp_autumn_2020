#include "Allocator.hpp"

Allocator::~Allocator() {
    if (!startPointer) {
        free(startPointer);
    }
}

void Allocator::makeAllocator(size_t maxSize) {
    if (startPointer != nullptr)
        return;
    if (!(startPointer = static_cast<char*>(malloc(maxSize)))) {
        std::cerr << "There is no place in heap with such space! Try to ask less or use another strategy!" << std::endl;
        return;
    }
    maxPossibleSize = maxSize;
    return;
}

char* Allocator::alloc(size_t size) {
    if (curPosition <= maxPossibleSize - size) {
        char* ptr = startPointer + curPosition;
        curPosition += size;
        return ptr;
    }
    else
        return nullptr;
}

void Allocator::reset() {
    curPosition = 0;
    return;
}

