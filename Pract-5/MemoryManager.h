#pragma once
#include <stdlib.h>


class MemoryManager {
private:
	size_t _size;
public:
	MemoryManager(size_t sz) : _size(sz) {}

	size_t size()
	{
		return _size;
	}

	virtual size_t maxBytes() { return -1; }

	virtual void* allocMem(size_t sz) = 0;

	virtual void freeMem(void* ptr) = 0;

};