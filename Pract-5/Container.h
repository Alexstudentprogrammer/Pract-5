#pragma once
#include <iostream>
#include "MemoryManager.h"
#pragma warning(disable:4996)

using namespace std;


class Container
{
protected:
	MemoryManager& _memory;
public:

	struct Error
	{
		char msg[256];
		Error(const char* err_msg)
		{
			strcpy(msg, err_msg);
		}
	};

	class Iterator
	{
	public:

		virtual void* getElement(size_t& size) = 0;//ask about necessity of keyword usage (virtual) in inverited classes

		virtual bool hasNext() = 0;

		virtual void goToNext() = 0;

		virtual bool equals(Iterator* right) = 0;
	};

	Container(MemoryManager& mem) : _memory(mem) {}


	virtual int size() = 0;


	virtual size_t max_bytes() = 0;


	virtual Iterator* find(void* elem, size_t size) = 0;


	virtual Iterator* newIterator() = 0;


	virtual void remove(Iterator* iter) = 0;


	virtual void clear() = 0;


	virtual bool empty() = 0;
};
