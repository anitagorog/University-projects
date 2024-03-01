#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

void SortedMultiMap::resize()
{
	auto new_list = new BSTNode[capacity * 2];
	auto new_left = new int[capacity * 2];
	auto new_right = new int[capacity * 2];

	for (int i = 0; i < capacity; i++)
	{
		new_list[i] = data[i];
		new_left[i] = left[i];
		new_right[i] = right[i];
	}
	for (int i = capacity; i < capacity * 2; i++)
	{
		new_left[i] = i + 1;
		new_right[i] = -1;
	}

	first_free = capacity;
	capacity *= 2;
	new_right[capacity - 1] = -1;
	new_left[capacity - 1] = -1;

	delete[] data;
	delete[] left;
	delete[] right;
	data = new_list;
	left = new_left;
	right = new_right;
}

void SortedMultiMap::remove_node(int pos, int prev)
{
	if (prev != -1) 
	{
		if (left[pos] == -1 && right[pos] == -1)
		{
			if (left[prev] == pos)
				left[prev] = -1;
			else 
				right[prev] = -1;

			left[pos] = first_free;
			first_free = pos;
			return;
		}
		if (left[pos] == -1 || right[pos] == -1)
		{
			int des;
			if (left[pos] != -1)
				des = left[pos];
			else
				des = right[pos];

			if (left[prev] == pos)
				left[prev] = des;
			else
				right[prev] = des;

			left[pos] = first_free;
			first_free = pos;
		}
		else
		{
			int current = pos;
			int previous = prev;
			while (left[current] != -1)
			{
				previous = current;
				current = left[current];
			}

			//delete data[pos].elem;
			data[pos] = data[current];

			this->remove_node(current, previous);

			left[current] = first_free;
			first_free = current;
		}
	}
	else //remove root
	{
		if (left[pos] == -1) //only right descendants
		{
			//delete[] data[pos].elems;
			head = right[pos];

			left[pos] = first_free;
			first_free = pos;

			return;
		}

		//delete[] data[pos].elems;
		head = left[pos];

		left[pos] = first_free;
		first_free = pos;
	}
}

BSTNode SortedMultiMap::create_node(TKey k)
{
	BSTNode n{};
	n.key = k;
	n.elem = NULL_TVALUE;
	return n;
}

SortedMultiMap::SortedMultiMap(Relation r) {
	this->r = r;
	this->capacity = 10;
	this->first_free = 0;
	this->data = new BSTNode[capacity];
	this->left = new int[capacity];
	this->right = new int[capacity];
	this->head = -1;
	this->nr_elems = 0;
	for (int i = 0; i < 10; i++)
	{
		left[i] = i + 1;
		right[i] = -1;
	}
	left[9] = -1;
}

void SortedMultiMap::add(TKey c, TValue v) {
	if (head == -1) //first elem
	{
		head = 0;
		data[head] = create_node(c);
		data[head].add(v);
		first_free = left[first_free];
		left[head] = -1;
		right[head] = -1;
		this->nr_elems++;
		return;
	}
	int current = this->head;
	int previous = -1;
	while (current != -1)
	{
		if (this->data[current].key == c)
			break;
		else if (this->r(data[current].key, c))
		{
			previous = current;
			current = right[current];
		}
		else if (!this->r(data[current].key, c))
		{
			previous = current;
			current = left[current];
		}
	}
	if (current != -1)
	{
		//if (this->data[current].size == this->data[current].capacity)
			//data[current].resize();
		if (first_free == -1)
			this->resize();
		/*if (this->r(data[current].key, c))
		{
			auto save_n = data[current];
			data[current] = create_node(c);
			data[current].add(v);
			while (right[current] != -1)
			{
				auto save_n2 = data[right[current]];
				data[right[current]] = save_n;
				save_n = save_n2;
				current = right[current];
			}
			this->first_free = right[current];
			right[current] = current;
			data[right[current]] = save_n;
			right[right[current]] = -1;
		}
		else if (!this->r(data[current].key, c))
		{*/
			auto save_n = data[current];
			data[current] = create_node(c);
			data[current].add(v);
			while (left[current] != -1)
			{
				auto save_n2 = data[left[current]];
				data[left[current]] = save_n;
				save_n = save_n2;
				current = left[current];
			}
			left[current] = first_free;
			data[first_free] = save_n;
			this->first_free = left[first_free];
			left[first_free] = -1;
		//}
		//this->data[current].add(v);
		this->nr_elems++;
	}
	if (current == -1)
	{
		if (first_free == -1)
			this->resize();
		current = first_free;
		this->data[current] = create_node(c);
		data[current].add(v);

		if (this->r(data[previous].key, c))
			right[previous] = current;
		else
			left[previous] = current;

		this->first_free = left[current];
		this->left[current] = -1;
		this->right[current] = -1;
		this->nr_elems++;
	}
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	int current = this->head;
	std::vector<TValue> elems;
	while (current != -1)
	{
		if (this->data[current].key == c)
			elems.push_back(this->data[current].elem);
		//if (!r(this->data[current].key, c))
			//current = left[current];
		//else if (r(this->data[current].key, c))
		current = left[current];
	}
	return elems;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	int current = this->head;
	int previous = -1;
	while (current != -1)
	{
		if (this->data[current].key == c && this->data[current].elem == v)
		{
			//if (!this->data[current].remove(v))
				//return false;
			//else //(this->data[current].size == 0)
			this->remove_node(current, previous);
			this->nr_elems--;
			return true;
		}
		/*else if (this->r(this->data[current].key, c))
		{
			previous = current;
			current = right[current];
		}
		else if (!this->r(this->data[current].key, c))
		{*/
			previous = current;
			current = left[current];
		//}
	}
	return false;
}

int SortedMultiMap::size() const {
	return this->nr_elems;
}

bool SortedMultiMap::isEmpty() const {
	if (this->nr_elems == 0)
		return true;
	return false;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {

}

void BSTNode::add(TValue e)
{
	//if (size == capacity)
		//resize();
	elem = e;
}

/*std::vector<TValue> BSTNode::get_values()
{
	std::vector<TValue> vec;
	vec.reserve(size);
	for (int i = 0; i < size; i++)
		vec.push_back(elems[i]);
	return vec;
}*/

/*void BSTNode::resize()
{
	auto new_l = new TValue[capacity * 2];
	for (int i = 0; i < capacity; i++)
		new_l[i] = elems[i];
	capacity *= 2;
	delete[] elems;
	elems = new_l;
}*/

bool BSTNode::remove(TValue e)
{
	/*for (int i = 0; i < size; i++)
		if (elems[i] == e)
		{
			elems[i] = elems[--size];
			return true;
		}*/
	if (elem == e)
	{
		elem = NULL_TVALUE;
		return true;
	}
	return false;
}
