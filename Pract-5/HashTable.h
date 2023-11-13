#pragma once
#include <list>
#include "my_vector.h"

//template <typename K, typename V>
class HashTable {

	struct Node {
		int key;
		int value;
	};
	Vector<Vector<Node*>> table;

public:
	HashTable() {

	}

	void put(int key, int value) {

	}

	Node* get(int key) {
		return NULL;
	}

};
