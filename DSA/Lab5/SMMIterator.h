#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& d);

	int current;
	BSTNode current_node;
	//struct Node {
		//int el; 
		//Node* next;
	//};
	//int stack_elems;
	//Node* stack_head;
	//void add_to_stack(int el);
	//void pop_from_stack();
	//int top();
	//int current_node;
	//int current_value;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

