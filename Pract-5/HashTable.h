#pragma once
#include <list>
#include "my_vector.h"
#include "KeyHash.h"

template <typename K, typename V, typename F = KeyHash>
class HashTable {
private:
	struct Node {
		K key;
		V value;
	};

	Vector<list<Node*>>* table;
	F hashFunction;

public:
	HashTable() {
		table = new Vector<list<Node*>>(100);
	}
	void put(K key, V value) {
		int position = hashFunction(key);
		list<Node*>* tmp = table->get(position);
		
		for (auto& node : *tmp)
		{
			if (node->key == key) {
				return;
			}
		}
		Node *node = new Node;

		node->key = key;
		node->value = value;
		tmp->push_back(node);
	}

	V& get(K key) {
		int position = hashFunction(key);
		list<Node*>* data = table->get(position);
		
		for (auto& node : *data)
		{
			if (node->key == key) {
				return node->value;
			}
		}	
	}
};
