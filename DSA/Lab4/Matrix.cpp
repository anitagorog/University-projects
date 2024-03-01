#include "Matrix.h"
#include <exception>
using namespace std;
#include <cstdlib>

//hash function
int Matrix::h(TElem e)
{
	return abs(e % this->m);
}
//Theta(1)

void Matrix::resize()
{
	auto ht = new NodePointer[this->m*2];
	
	for (int i = 0; i < 2*m; i++)
	{
		ht[i] = nullptr;
	}
	Node* newNode;
	for (int x = 0; x < m; x++)
	{
		newNode = this->hashTable[x];
		while (newNode != nullptr)
		{
			TElem e = std::get<0>(newNode->info);
			int pos = h(e);
			if (ht[pos] == nullptr)
			{
				ht[pos] = newNode;
			}
			else {
				newNode->next = ht[pos];
				ht[pos] = newNode;
			}
			newNode = newNode->next;
		}
	}
	delete[] this->hashTable;
	this->hashTable = ht;
	this->m = m * 2;
}
//Theta(m) - previous m

Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->n = 0;
	this->m = 11;
	this->hashTable = new NodePointer[this->m];
	for (int i = 0; i < m; i++)
	{
		this->hashTable[i] = nullptr;
	}

	this->nr_lines = nrLines;
	this->nr_columns = nrCols;
}
//Theta(1)

int Matrix::numberOfNonZeroElems(int col) const
{
	if (col >= this->nr_columns || col < 0)
		throw std::exception();
	int nr = 0;
	Node* newNode;
	for (int x = 0; x < m; x++) 
	{
		newNode = this->hashTable[x];
		while (newNode != nullptr)
		{
			if (std::get<1>(newNode->info) == col && std::get<2>(newNode->info) != NULL_TELEM)
			{
				nr++;
			}
			newNode = newNode->next;
		}
	}
	return nr;
}
//Theta(m)


int Matrix::nrLines() const {
	return this->nr_lines;
}
//Theta(1)


int Matrix::nrColumns() const {
	return this->nr_columns;
}
//Theta(1)


TElem Matrix::element(int i, int j) const {
	if (i >= this->nr_lines || i < 0 || j >= this->nr_columns || j < 0)
		throw std::exception();
	int x = 0;
	Node* newNode = this->hashTable[x];
	while (x<m) {
		while (newNode != nullptr)
		{
			if (std::get<0>(newNode->info) == i && std::get<1>(newNode->info) == j)
			{
				return std::get<2>(newNode->info);
			}
			newNode = newNode->next;
		}
		x++;
		newNode = this->hashTable[x];
	}
	return NULL_TELEM;
}
// Theta(m)

TElem Matrix::modify(int i, int j, TElem e) {
	if (i >= this->nr_lines || i < 0 || j >= this->nr_columns || j < 0)
		throw std::exception();
	int pos = this->h(e);
	int x = 0;
	TElem prev_e = NULL_TELEM;
	Node* currNode = this->hashTable[x];
	while (x < m) 
	{
		while(currNode != nullptr)
		{
			if (std::get<0>(currNode->info) == i && std::get<1>(currNode->info) == j)
			{
				prev_e = std::get<2>(currNode->info);
				if (this->hashTable[x] == currNode)
				{
					this->hashTable[x] = this->hashTable[x]->next;
				}
				else {
					Node* curr2Node = this->hashTable[x];
					while (std::get<0>(curr2Node->next->info) != i || std::get<1>(curr2Node->next->info) != j || std::get<2>(curr2Node->next->info) != prev_e)
					{
						curr2Node = curr2Node->next;
					}
					curr2Node->next = curr2Node->next->next;
				}
				n--;
			}
			currNode = currNode->next;
		}
		x++;
		currNode = this->hashTable[x];
	}
	Node* newNode = new Node(i, j, e);
	if (this->hashTable[pos] == nullptr)
	{
		hashTable[pos] = newNode;
	}
	else {
		newNode->next = this->hashTable[pos];
		hashTable[pos] = newNode;
	}
	n++;
	if ((double)n / (double)m < double(1 / 7))
		this->resize();
	return prev_e;
}
//Theta(m)

