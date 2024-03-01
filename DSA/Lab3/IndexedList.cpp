#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

void IndexedList::resize()
{
    capacity *= 2;
    SLLANode* copy = new SLLANode[capacity];
    for (int i = 0; i < first_free; i++)
        copy[i] = this->elements[i];
    
    this->elements = copy;
}

IndexedList::IndexedList() {
    this->capacity = 10;
    this->elements = new SLLANode[capacity];
    this->first_free = 0;
    this->head = -1;
    this->length = 0;
}
//Theta(1)

int IndexedList::size() const {
    return this->length;
}
//Theta(1)

bool IndexedList::isEmpty() const {
    if (this->length == 0)
        return true;
    return false;
}
//Theta(1)

TElem IndexedList::getElement(int pos) const {
    if (pos < 0 || pos >= first_free)
        throw std::exception();
    return this->elements[pos].elem;

}
//Theta(1)

TElem IndexedList::setElement(int pos, TElem e) {
    if (pos < 0 || pos >= first_free)
        throw std::exception();
    TElem old_elem = this->elements[pos].elem;
    this->elements[pos].elem = e;
    return old_elem;  
}
//Theta(1)

void IndexedList::addToEnd(TElem e) {
    if (this->length == this->capacity)
        this->resize();
    if (this->isEmpty())
        this->head = this->first_free;
    this->elements[this->first_free].elem = e;
    this->elements[(this->first_free) - 1].next = this->first_free;
    this->first_free++;
    this->length++;
}
//Theta(1)

void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 || pos >= first_free)
        throw std::exception();
    if (this->length == this->capacity)
        this->resize();
    if (this->isEmpty())
    {
        this->elements[pos].elem = e;
        this->elements[pos].next = -1;
        this->head = pos;
    }
    else
    {
        int curr = this->head;
        while (curr != pos && curr != -1)
        {
            curr = this->elements[curr].next;
        }
        if (curr == -1)
        {
            this->elements[curr].next = pos;
            this->elements[pos].elem = e;
        }
        else {
            int sve_value;
            int ad_value = e;
            while (this->elements[curr].next != -1)
            {
                sve_value = this->elements[curr].elem;
                this->elements[curr].elem = ad_value;
                ad_value = sve_value;
                curr = this->elements[curr].next;
            }
            sve_value = this->elements[curr].elem;
            this->elements[curr].elem = ad_value;
            ad_value = sve_value;

            this->elements[curr].next = this->first_free;
            this->first_free++;
            curr = this->elements[curr].next;
            this->elements[curr].elem = ad_value;
        }

    }
    this->length++;
}
//O(length)

TElem IndexedList::remove(int pos) {
    if (pos < 0 || pos >= first_free || this->elements[pos].elem == NULL_TELEM)
        throw std::exception();
    if (pos == head) {
        this->length--;
        TElem sve = this->elements[head].elem;
        this->elements[head].elem = NULL_TELEM;
        head = this->elements[head].next;
        return sve;
    }
    TElem removed_element = this->elements[pos].elem;
    TElem current = this->head;
    while (this->elements[current].next != pos && this->elements[current].next != -1)
    {
        current = this->elements[current].next;
    }
    current = this->elements[current].next; 
    if (this->elements[current].next == -1)
    {
        this->elements[pos - 1].next = -1;
        this->elements[pos].elem = NULL_TELEM;
        
    }
    else {
        while (this->elements[current].next != -1)
        {
            this->elements[current].elem = this->elements[this->elements[current].next].elem;
            
            if (this->elements[this->elements[current].next].next == -1)
                this->elements[current].next = -1;
            else
                current = this->elements[current].next;
        }
        
        this->elements[this->elements[current].next].elem = NULL_TELEM;
    }

    this->length--;
    this->first_free--;
    return removed_element;
}
//O(length)

int IndexedList::search(TElem e) const{
    if (this->isEmpty())
        return -1;
    if (this->elements[head].elem == e)
        return head;
    int current = this->head;
    while (current != -1 && this->elements[current].elem != e)
        current = this->elements[current].next;
    return current;
}
//O(length)

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}
//Theta(1)

IndexedList::~IndexedList() {
}




int IndexedList::lastIndexOf(TElem elem) const
{
    if (this->isEmpty())
        return -1;
    int curren = head;
    int the_index = -1;
    while (this->elements[curren].next != -1)
    {
        if (this->elements[curren].elem == elem)
            the_index = curren;
        curren = this->elements[curren].next;
    }
    if (this->elements[curren].elem == elem)
        the_index = curren;
    return the_index;
}
