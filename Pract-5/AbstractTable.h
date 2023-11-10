#pragma once
#pragma once
#include "GroupContainer.h"


class AbstractTable : public GroupContainer
{
public:

	AbstractTable(MemoryManager& mem) : GroupContainer(mem) {}

	// Write implementation in one field using group container methods
	virtual ~AbstractTable() {}

	virtual int insertByKey(void* key, size_t keySize, void* elem, size_t elemSize) = 0;

	virtual void removeByKey(void* key, size_t keySize) = 0;

	virtual Iterator* findByKey(void* key, size_t keySize) = 0;

	virtual void* at(void* key, size_t keySize, size_t& valueSize) = 0;

	virtual size_t hash_function(void* key, size_t keySize) = 0;//move to GroupContainer
};

