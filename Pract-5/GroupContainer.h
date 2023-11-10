#pragma once
#include "Container.h"
#include "list.h"
class GroupContainer : public Container {
protected:
	int elements;
	int table_size;
	SLinkedListList** hash_table;//TODO rename this !!!!!
	//declare Node (from list0 and make it as friend for list)
	//add table compression

public:
	GroupContainer(MemoryManager& mem) : Container(mem) {
		hash_table = new SLinkedListList * [500000];
		for (int i = 0; i < 500000; i++) {
			*(hash_table + i) = new SLinkedListList(mem);
		}
		table_size = 500000;
		elements = 0;

	}

	/* class BaseNode {
	protected:
		void* value;
		size_t size;
	public:
		BaseNode(void* value, size_t val_size) {
			this->value = value;
			this->size = val_size;
		}

		void* getValue() {
			return value;
		}
		size_t getValSize() {
			return size;
		}
	};*/

	size_t hash_f(void* key, size_t keySize) {
		size_t hash = 0;
		char* temp = static_cast<char*>(key);
		for (int i = 0; i < keySize; ++i) {
			hash *= 85021;
			hash = hash + temp[i];
			hash %= 130253;
		}
		return hash % table_size;
	};

	void clear() {
		for (int i = 0; i < table_size; i++) {
			hash_table[i]->clear();
			delete hash_table[i];
		}
		delete[] hash_table;
	};
	bool empty() {
		return elements == 0;
	};

	Iterator* find(void* elem, size_t size) {
		int hash = hash_f(elem, size);
		SLinkedListList* list = hash_table[hash];
		SLinkedListList::Iterator tmp = list->begin();//same as set

		for (; tmp != NULL; ++tmp) {
			Iterator* iterator = checkElement(elem, size, tmp, hash);
			if (iterator != NULL)
				return iterator;
		}
		return NULL;
	};
	int size() {
		return table_size;
	};
	size_t max_bytes() {
		return _memory.maxBytes();

	};

protected:
	virtual Iterator* checkElement(void* key, size_t keySize, SLinkedListList::Iterator tmp, int hash) = 0;

};

