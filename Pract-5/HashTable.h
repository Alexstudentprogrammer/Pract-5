#pragma once
#include"AbstractTable.h"
#include "Mem.h"
#include <ctime>
#include <vector>
#include "list.h"

class HashTable : public  AbstractTable {
	class TableIterator;

public:
	HashTable(MemoryManager& mem) : memory(mem), AbstractTable(mem) {

	}

private:
	MemoryManager& memory;
	int iter_count = 0;

	class TableNode {
	private:
		void* key = NULL;
		size_t key_size;// TODO include Node declaration in GroupContainer class
		void* value;
		size_t size;

	public:
		TableNode(void* key, size_t kSize, void* val, size_t valSize, MemoryManager& mem) {



			//this->key = malloc(kSize);
			this->key = (void*)mem.allocMem(kSize);
			memcpy(this->key, key, kSize);

			//this->value = malloc(valSize);
			this->value = (void*)mem.allocMem(valSize);
			memcpy(this->value, val, valSize);

			key_size = kSize;
			size = valSize;

		}
		void* getValue() {
			return value;
		}
		size_t getValSize() {
			return size;
		}
		void* getKey() {
			return key;
		}
		size_t getKeySize() {
			return key_size;
		}


		~TableNode() {
		}
		friend class HashTable::TableIterator;
		friend class HashTable;
	};

	int maxsize = 0;
	int minsize = 10000000;


	class TableIterator : public Container::Iterator {// can be renamed to Iterator (think about inheritance of list iterator)

	private:

		SLinkedListList::Iterator* iter = NULL;
		SLinkedListList** buckets_link;
		int bucket;
		int total;
		int* iter_count;
	public:
		TableIterator(SLinkedListList** b, int bucket, int total, int iter_count) {
			//current = node;
			buckets_link = b;// added link to buckets
			this->total = total;
			this->bucket = bucket;
			this->iter_count = &iter_count;
			iter = buckets_link[bucket]->newIterator();//was recently added

		}
		virtual void* getElement(size_t& size) {
			size_t size_of_node = sizeof(TableNode);
			TableNode* gained_node = (TableNode*)iter->getElement(size_of_node);
			return gained_node->getValue();

		};
		bool hasElement() {
			if (iter != NULL && iter->hasElement())
				return true;

			return false;
		}
		bool hasNext() {//TODO displacement of iterator in hasNext() (replace it to goToNext) but we also need to check
			if (iter != NULL && iter->hasElement()) {//TAKE A LOOK
				return true;
			}
			else {
				for (; bucket + 1 < total; bucket++) {
					if (!buckets_link[bucket + 1]->empty()) {
						delete iter;
						iter = (SLinkedListList::Iterator*)buckets_link[bucket + 1]->newIterator();
						bucket++;
						return true;
					}
				}//initialize TOTAL
				return false;
			}
		};

		void goToNext() {
			iter->goToNext();// TODO guarantee the next element here
		};

		bool equals(Iterator* right) {
			if (iter == right)
				return true;
			return false;
		};

		~TableIterator() {
			iter_count--;
		}
		friend class HashTable;
	};

	Iterator* newIterator() {
		for (int i = 0; i < table_size; i++) {
			if (!hash_table[i]->empty()) {
				TableIterator* iterator = new TableIterator(hash_table, i, table_size, iter_count);

				iter_count++;
				return iterator;
			}
		}
		return NULL;
	};
	void remove(Iterator* iter) {
		TableIterator* iterator = (TableIterator*)(iter);
		size_t cell_size = sizeof(TableNode);
		TableNode* cell = (TableNode*)(iterator->getElement(cell_size));

		removeByKey(cell->getKey(), cell->getKeySize());
		delete iterator;
	};
	int insertByKey(void* key, size_t keySize, void* elem, size_t elemSize) {//handle insertion of existing element

		int hash = hash_function(key, keySize);
		SLinkedListList* list = hash_table[hash];
		Iterator* iter = findByKey(key, keySize);
		if (iter != NULL) {
			delete iter;
			return 1;
		}


		TableNode* node = new TableNode(key, keySize, elem, elemSize, memory);

		list->push_front(node, sizeof(TableNode));
		maxsize = max(maxsize, list->size());
		elements++;

		if (elements >= table_size * 4 && iter_count == 0) {//TODO make as user's parameters

			if (maxsize > (100)) {
				maxsize = 0;
				rehash();
			}
		}
		delete node;
		return 0;
	};
	virtual void removeByKey(void* key, size_t keySize) {

		int hash = hash_function(key, keySize);
		SLinkedListList* list = hash_table[hash];

		SLinkedListList::Iterator* tmp = (SLinkedListList::Iterator*)list->newIterator();
		if (tmp != NULL) {
			do {
				size_t size = tmp->getDataSize();
				TableNode* node = (TableNode*)tmp->getElement(size);

				if (node->getKeySize() == keySize && memcmp(node->getKey(), key, keySize) == 0) {
					list->remove(tmp);
					break;
				}

				tmp->goToNext();
			} while (tmp->hasElement());
			delete tmp;// was uncommented
		}
	};
	virtual Iterator* findByKey(void* key, size_t keySize) {

		TableIterator* it = (TableIterator*)GroupContainer::find(key, keySize);
		if (it != NULL)
			return it;
		//int hash = hash_function(key, keySize);
		//SLinkedListList* list = hash_table[hash];
		//SLinkedListList::Iterator tmp = list->begin();//same as set

		//if (tmp != NULL) {
		//	do {
		//		size_t size = sizeof(TableNode);

		//		TableNode* node = (TableNode*)tmp->getElement(size);
		//		if (node->getKeySize() == keySize && memcmp(node->getKey(), key, keySize) == 0) {
		//			TableIterator* table_iter = new TableIterator(hash_table, hash, table_size, iter_count);
		//			table_iter->iter = tmp;
		//			return table_iter;
		//		}// not same (192 - 196) make virtual function

		//		tmp->goToNext();
		//	} while (tmp->hasElement());
		//}

		/*for (; tmp != NULL; ++tmp) {

			size_t size = sizeof(TableNode);
			TableNode* node = (TableNode*)tmp.getElement(size);
			if (node->getKeySize() == keySize && memcmp(node->getKey(), key, keySize) == 0) {
							TableIterator* table_iter = new TableIterator(hash_table, hash, table_size, iter_count);
							SLinkedListList::Iterator *tmp_iter = new SLinkedListList::Iterator(tmp.getCurrentNode());
							table_iter->iter = tmp_iter;
							return table_iter;
			}
		}*/

		return NULL;
	};

	virtual Iterator* checkElement(void* key, size_t keySize, SLinkedListList::Iterator tmp, int hash) {
		//give iterator as marameter

		size_t size = sizeof(TableNode);
		TableNode* node = (TableNode*)tmp.getElement(size);
		if (node->getKeySize() == keySize && memcmp(node->getKey(), key, keySize) == 0) {
			TableIterator* table_iter = new TableIterator(hash_table, hash, table_size, iter_count);
			SLinkedListList::Iterator* tmp_iter = new SLinkedListList::Iterator(tmp.getCurrentNode());
			table_iter->iter = tmp_iter;
			return table_iter;
		}
		return NULL;
	}

	virtual void* at(void* key, size_t keySize, size_t& valueSize) {

		int hash = hash_function(key, keySize);
		SLinkedListList* list = hash_table[hash];

		SLinkedListList::Iterator* iterator = (SLinkedListList::Iterator*)list->newIterator();
		if (iterator != nullptr) {
			do {

				SLinkedListList::Iterator* tmp = (SLinkedListList::Iterator*)iterator;
				if (tmp != nullptr) {
					size_t size = tmp->getDataSize();

					TableNode* node = (TableNode*)tmp->getElement(size);
					if (node->getKeySize() == keySize && memcmp(node->getKey(), key, keySize) == 0) {
						delete iterator;
						valueSize = node->getValSize();
						return node->getValue();
					}
				}
				iterator->goToNext();
			} while (iterator->hasElement());
		}
		delete iterator;
		return NULL;
	};
	virtual size_t hash_function(void* key, size_t keySize) {
		return hash_f(key, keySize);
	};

	int checkFormin() {
		for (int i = 0; i < table_size; i++) {
			minsize = min(hash_table[i]->size(), minsize);
		}

		return minsize;
	}
	int getMaxSize() {
		for (int i = 0; i < table_size; i++) {
			maxsize = max(hash_table[i]->size(), maxsize);
		}
		return maxsize;
	}
	void makeHistogram(vector<int>& vec) {

		for (int i = 0; i < table_size; i++) {

			switch (hash_table[i]->size()) {
			case 0://size 
				vec[0]++;
				break;

			case 1://size 
				vec[1]++;
				break;

			case 2://size 
				vec[2]++;
				break;

			case 3://size 
				vec[3]++;
				break;

			case 4://size 
				vec[4]++;
				break;

			case 5://size 
				vec[5]++;
				break;

			case 6://size 
				vec[6]++;
				break;

			case 7://size 
				vec[7]++;
				break;

			case 8://size 
				vec[8]++;
				break;

			case 9://size 
				vec[9]++;
				break;

			case 10://size 
				vec[10]++;
				break;

			case 11://size 
				vec[11]++;
				break;

			case 12://size 
				vec[12]++;
				break;

			case 13://size 
				vec[13]++;
				break;

			case 14://size 
				vec[14]++;
				break;

			case 15://size 
				vec[15]++;
				break;

			case 16://size 
				vec[16]++;
				break;

			case 17://size 
				vec[17]++;
				break;

			case 18://size 
				vec[18]++;
				break;

			case 19://size 
				vec[19]++;
				break;

			case 20://size 
				vec[20]++;
				break;

			}
		}
	}


private:
	clock_t total_time = 0;
	void rehash() {
		clock_t start_clock = clock();
		table_size *= 2;

		SLinkedListList** new_buckets = new SLinkedListList * [table_size];
		for (int i = 0; i < table_size; i++) {
			*(new_buckets + i) = new SLinkedListList(memory);
		}

		int tot = 0;
		for (int i = 0; i < (table_size / 2); i++) {

			if (!hash_table[i]->empty()) {

				SLinkedListList::Iterator* start = (SLinkedListList::Iterator*)hash_table[i]->newIterator();
				do {
					//ask for key from iterator 
					size_t size = sizeof(TableNode);
					TableNode* node = (TableNode*)start->getElement(size);
					int h = hash_function(node->getKey(), node->getKeySize());

					SLinkedListList* ls = new_buckets[h];
					ls->push_front(node, sizeof(TableNode));

					maxsize = max(maxsize, ls->size());
					hash_table[i]->remove(start);
					tot++;

				} while (start->hasElement());//"has next" had been removed
				delete start;
			}
		}
		for (int i = 0; i < table_size / 4; i++) {
			delete hash_table[i];
		}
		delete[] hash_table;

		hash_table = new_buckets;

	}


};
