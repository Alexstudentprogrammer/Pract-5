#pragma once
#include "MemoryManager.h"

class Mem : public MemoryManager
{
public:
	Mem(size_t sz) : MemoryManager(sz) {}

	void* allocMem(size_t sz)
	{
		return new char[sz];
	}

	void freeMem(void* ptr)
	{
		delete[] ptr;
	}
};
