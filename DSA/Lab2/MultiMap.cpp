#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	this->length = 0;
	this->head = new Node;
	this->tail = new Node;
}
//Theta(1)


void MultiMap::add(TKey c, TValue v) {
	Node *new_node = new Node;
	TElem elem = TElem(c, v);
	new_node->e = elem;
	if (this->length == 0)
	{
		this->head = new_node;
		this->tail = new_node;
		this->head->next = tail;
		this->tail->previous = head;
	}
	else if(this->length == 1)
	{
		this->tail = new_node;
		this->head->next = tail;
		this->tail->previous = head;
	}
	else
	{
		this->tail->next = new_node;
		new_node->previous = this->tail;
		this->tail = new_node;
	}
	this->length++;
}
//Theta(1)


bool MultiMap::remove(TKey c, TValue v) {
	Node* current = this->head;
	if (this->length == 1)
	{
		if (current->e.first == c && current->e.second == v)
		{
			this->head = new Node;
			this->tail = new Node;
			this->length--;
			return true;
		}
		else 
			return false;
	}
	while (current->next != nullptr)
	{
		if (current->e.first == c && current->e.second == v)
		{
			if (current == this->head)
			{
				if (this->length == 2)
				{
					this->head = this->tail;
					this->head->next = tail;
					this->head->previous = nullptr;
				}
				/*else if (this->length == 1)
				{
					this->head = new Node;
					this->tail = new Node;
				}*/
				else {
					this->head = this->head->next;
					this->head->previous = nullptr;
				}
			}
			else{
				current->previous->next = current->next;
				current->next->previous = current->previous;
			}

			this->length--;
			return true;
		}
		current = current->next;
	}
	if (this->tail->e.first == c && this->tail->e.second == v)
	{
		if (this->length == 2)
		{
			this->tail = this->head;
			this->tail->next = nullptr;
			this->tail->previous = head;
		}
		else {
			//this->tail->previous->next = nullptr;
			this->tail = this->tail->previous;
			this->tail->next = nullptr;
			// jo napot!
		}
		
		this->length--;
		return true;
	}
	return false;
}
//O(length)


vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> values_of_c;
	Node* current = this->head;
	if (this->length == 1)
	{
		if (current->e.first == c)
			values_of_c.push_back(current->e.second);
		return values_of_c;
	}
	while (current != nullptr)
	{
		if (current->e.first == c)
			values_of_c.push_back(current->e.second);
		current = current->next;
	}
	return values_of_c;
}
//Theta(length)


int MultiMap::size() const {
	return this->length;
}
//Theta(1)


bool MultiMap::isEmpty() const {
	if (this->length == 0)
		return true;
	return false;
}
//Theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
//Theta(1)


MultiMap::~MultiMap() {
	Node* current = this->head;
	while (current != nullptr)
	{
		Node* save_next = current->next;
		delete current;
		current = save_next;
	}
}
//Theta(length)

int MultiMap::getValueRange() const
{
	if (this->isEmpty())
		return -1;
	if (this->length == 1)
		return 0;
	Node* current_n = this->head;
	int max_v = this->head->e.second;
	int	min_v = this->head->e.second;
	while (current_n != nullptr)
	{
		if (current_n->e.second > max_v)
		{
			max_v = current_n->e.second;
		}
		if (current_n->e.second < min_v)
		{
			min_v = current_n->e.second;
		}
		current_n = current_n->next;
	}
	return max_v - min_v;
}
//Theta(length)

