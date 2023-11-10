#pragma once
#include "list.h"


SLinkedListList::SLinkedListList(MemoryManager& mem) : AbstractList(mem)
{
	size_ = 0;
	head = nullptr;
	tail = nullptr;
}
//container
//size
//max_bytes
//empty
SLinkedListList::Iterator* SLinkedListList::find(void* elem, size_t size)
{
	Node* current = head;
	while (current != NULL)
	{
		if (current->size == size)
		{
			if (memcmp(current->value, elem, size) == 0)
			{
				SLinkedListList::Iterator* iter = new SLinkedListList::Iterator(current);
				return iter;
			}
		}
	}
	return NULL;
};
SLinkedListList::Iterator* SLinkedListList::newIterator()
{
	if (head == NULL) return NULL;
	SLinkedListList::Iterator* iterator = new SLinkedListList::Iterator(head);
	return iterator;
};
void SLinkedListList::remove(Container::Iterator* iter) {

	SLinkedListList::Iterator* iterator = (SLinkedListList::Iterator*)iter;
	removeNode(iterator);
}

void SLinkedListList::removeNode(SLinkedListList::Iterator* it)
{
	SLinkedListList::Node* it_node = it->getCurrentNode();
	SLinkedListList::Node* pr = head;
	if (it->hasNext())
	{
		it->goToNext();
	}
	else
	{
		*it = NULL;
	}

	if (pr == it_node)
	{
		if (pr->next != NULL) { head = pr->next; }
		else { head = NULL; }
		delete pr;
		size_--;
		return;
	}


	while (pr != NULL)
	{
		if (pr->next == it_node)
		{
			SLinkedListList::Node* finded = pr->next;
			pr->next = finded->next;
			delete finded;
			size_--;
		}
		pr = pr->next;
	}
}
//void SLinkedListList::removeNode(SLinkedListList::Iterator* iterator) {// problem with first element removal
//	
//	Node* node = iterator->getCurrentNode();
//	if (iterator->hasElement()) {
//		iterator->goToNext();
//	}
//	
//	Node* pre = NULL;
//	Node* cur = head;
//
//	while (cur != NULL) {
//		if (cur == node) {
//			if (pre == NULL) {
//				
//				Node* tmp = head->next;
//				delete head;
//				head = tmp;
//				this->size_--;
//				break;
//			}
//			else {
//				pre->next = cur->next;
//				delete cur;
//				this->size_--;
//				break;
//			}
//		}
//		else {
//			pre = cur;
//			cur = cur->next;
//		}
//	}
//}
void SLinkedListList::clear()
{

	Node* tmp; //= head->next;
	while (head != NULL) {
		Node* tmp = head->next;
		delete head;
		head = tmp;
	}
};




//List_Abstract
int SLinkedListList::push_front(void* elem, size_t size) {
	Node* node = new Node;//MM usage (Best fit)
	node->size = size;
	node->value = malloc(size);// MM usage
	memcpy(node->value, elem, node->size);

	if (head == NULL) {
		head = node;
	}
	else {
		node->next = head;
		head = node;
	}
	this->size_++;
	return 1;
}

void  SLinkedListList::pop_front()
{
	Node* head_next = head->next;
	SLinkedListList::Iterator it = this->begin();
	removeNode(&it);
	head = head->next;
}


void* SLinkedListList::front(size_t& size)
{
	size = head->size;
	return head;
}


int   SLinkedListList::insert(Container::Iterator* iter, void* elem, size_t elemSize)
{
	head = head->next;
	return 1;
}


// 
//begin
//end
bool SLinkedListList::firstNode(Node* node)
{

	if (head == nullptr)
	{
		head = node;
		tail = node;
		head->next = tail;
		tail->next = NULL;
		return true;
	}
	return false;
}

SLinkedListList::Node* SLinkedListList::newNode(size_t size, void* elem)
{
	Node* node = new Node;
	node->size = size;
	node->value = malloc(size);
	memcpy(node->value, elem, node->size);
	size_++;
	return node;
}



void SLinkedListList::push_back(size_t size, void* elem)
{
	Node* node = newNode(size, elem);
	if (firstNode(node)) return;
	tail->next = node;
	tail = node;
}



