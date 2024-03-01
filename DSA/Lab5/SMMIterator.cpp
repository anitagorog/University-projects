#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	current_node = this->map.data[0];
	current = 0;
}

void SMMIterator::first(){
	this->current_node = this->map.data[0];
}

void SMMIterator::next(){
	current = this->map.left[current];
	this->current_node = this->map.data[current];
}

bool SMMIterator::valid() const{
	if (current == -1)
		return false;
	return true;
}

TElem SMMIterator::getCurrent() const{
	TElem current_pair = TElem(this->current_node.key, this->current_node.elem);
	return current_pair;
}


