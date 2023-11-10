#pragma once
#include "ListAbstract.h"


class SLinkedListList : public AbstractList
{
private:

	class Node
	{
	public:
		Node* next;
		void* value;
		size_t size;
		Node()
		{
			next = NULL;
			value;
			size = 0;
		}

		~Node()
		{

			delete value;
		}

	};

	Node* head;
	Node* tail;
	int   size_;

public:
	class Iterator : public Container::Iterator
	{
	private: Node* current;

	public:

		void* getElement(size_t& size)			 override { size = current->size;  return current->value; }
		bool  hasNext()							 override { return current->next != NULL; }
		void  goToNext()						 override { current = current->next; }
		bool  equals(Container::Iterator* right) override { return current == ((SLinkedListList::Iterator*)right)->current; }

		SLinkedListList::Iterator(Node* cur) { current = cur; }
		SLinkedListList::Iterator(const SLinkedListList::Iterator& other) { current = other.current; }

		size_t getDataSize() { return current->size; }
		Node* getCurrentNode() { return current; }
		void   putCurrentNode(Node* val) { current = val; }
		bool   hasElement() { return current != NULL; }

		void* operator*  (size_t& size) { return getElement(size); }
		bool      operator== (const SLinkedListList::Iterator& right) const { return current == right.current; }
		bool      operator!= (const SLinkedListList::Iterator& right) const { return !(*this == right); }
		Iterator& operator++ () { this->current = this->current->next; return *this; }
		Iterator& operator+ (int n) const
		{
			Iterator temp = *this;
			for (size_t i = 0; i < n; i++) { ++temp; }
			return temp;
		}
	};


	SLinkedListList(MemoryManager& mem);

	//container
	int		  size()								  override { return size_; }
	size_t    max_bytes()							  override { return _memory.maxBytes(); };
	Iterator* find(void* elem, size_t size)           override;
	Iterator* newIterator()				              override;
	void      remove(Container::Iterator* iter)       override;
	void      clear()								  override;
	bool	  empty()								  override { return head == NULL; };

	//List_Abstract
	int   push_front(void* elem, size_t elemSize)			             override;
	void  pop_front()										             override;
	void* front(size_t& size)								             override;
	int   insert(Container::Iterator* iter, void* elem, size_t elemSize) override;


	Iterator begin() { return SLinkedListList::Iterator(head); }
	Iterator end() { return SLinkedListList::Iterator(tail); }
	bool	 firstNode(Node* node);
	Node* newNode(size_t size, void* elem);
	void	 push_back(size_t size, void* elem);
private:
	void removeNode(Iterator* it);
};
