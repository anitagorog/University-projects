#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->current = this->col.head;
}
//Theta(1)

TElem MultiMapIterator::getCurrent() const{
	if (col.isEmpty())
		throw exception();
	if (this->current == nullptr)
	{
		throw exception();
	}
	return this->current->e;
}
//Theta(1)

bool MultiMapIterator::valid() const {
	if (this->col.isEmpty())
		return false;
	if (this->current == nullptr)
		return false;
	return true;
}
//Theta(1)

void MultiMapIterator::next() {
	if (col.isEmpty())
		throw exception();
	/*if (this->current == nullptr)
	{
		this->first();
		return;
	}//if it's not declared yet -> takes the first element*/
	if (this->col.length == 1)
	{
		this->current = nullptr;
		return;
	}
	/*if (this->current->next == nullptr)
	{
		this->first();
		return;
	}//if it got to the end -> takes the first element*/
	this->current = this->current->next;
}
//Theta(1)

void MultiMapIterator::first() {
	if (col.isEmpty())
		throw exception();
	this->current = this->col.head;
}
//Theta(1)
