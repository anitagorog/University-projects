#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	this->length = 0;
	this->capacity = 10;
	this->r = r;
	this->elements = new TElem[capacity];
}
//Theta(1)


bool SortedSet::add(TComp elem) {
	if (this->length == 0)
	{
		this->elements[0] = elem;
		this->length++;
		return true;
	}
	else {
		int index=(this->length)-1;
		while ( r(this->elements[index], elem) == false && index >= 0 )
		{
			index--;
		}
		index++;
		// gets the index where we need to put the new element
		// where the relation becomes true
		if (this->elements[index - 1] == elem) // NOT || INDEX
			return false;
		// if already there return false
		else {
			if (this->capacity == this->length)
				this->resize();
			if (index == length)
			{
				this->elements[index] = elem;
			}
			else {
				for (int i = this->length; i > index; i--)
				{
					this->elements[i] = this->elements[i - 1];
				}
				this->elements[index] = elem;
			}
			this->length++;
			return true;
		}
	}
}
//best case: Theta(1) (when it is empty)
//worst and average case: Theta(length)  (>> being 2*length)


bool SortedSet::remove(TComp elem) {
	int index = 0;
	bool found = false;
	while (index < this->length && found == false)
	{
		if (this->elements[index] == elem)
			found = true;
		else
			index++;
	}
	if (found == false)
	{
		return false;
	}
	else {
		while (index < this->length - 1)
		{
			this->elements[index] = this->elements[index + 1];
			index++;
		}
		this->length--;
		return true;
	}
}
//best case: Theta(1)
//worst and average case: Theta(length)


bool SortedSet::search(TComp elem) const {
	int index = 0;
	while (index < this->length)
	{
		if (this->elements[index] == elem)
			return true;
		index++;
	}
	return false;
}
//best case: Theta(1)
//worst and average case: Theta(length)


int SortedSet::size() const {
	return this->length;
}
//Theta(1)



bool SortedSet::isEmpty() const {
	if (this->length == 0)
		return true;
	return false;
}
//Theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	delete[] this->elements;
}
//Theta(1)


void SortedSet::resize() {
	int newCapacity = 2 * this->capacity;
	TElem* newElements = new TElem[newCapacity];

	for (int i = 0; i < this->capacity && i < this->length; i++)
		newElements[i] = this->elements[i];

	delete[] this->elements;
	this->capacity = newCapacity;
	this->elements = newElements;

}
//Theta(length)

int SortedSet::getRange() const
{
	if (this->length == 0)
		return -1;
	int range = this->elements[0] - this->elements[this->length - 1];
	if (range < 0)
		return -range;
	return range;
}
//Theta(1)
