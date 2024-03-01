#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(const IndexedList& list) : list(list){
    if (this->list.isEmpty())
        this->position = -1;
    else
        this->position = this->list.head;
}
//Theta(1)

void ListIterator::first(){
    if (this->list.isEmpty())
        this->position = -1;
    else
        this->position = this->list.head;
}
//Theta(1)

void ListIterator::next(){
    if (this->position == -1)
        throw std::exception();
    else
        this->position = this->list.elements[this->position].next;
}
//Theta(1)

bool ListIterator::valid() const{
    if (position == -1)
        return false;
    return true;
}
//Theta(1)

TElem ListIterator::getCurrent() const{
    if (!valid())
        throw std::exception();
    else
        return this->list.elements[this->position].elem;
}
//Theta(1)
