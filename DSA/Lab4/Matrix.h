#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

#include <tuple>
using std::tuple;
using std::make_tuple;
typedef tuple<int, int, TElem> mTuple;
//SLL NODE
struct Node {
	mTuple info;
	Node* next;
	Node(int row, int col, TElem info) : info(make_tuple(row, col, info)), next(nullptr)
	{
	}
};
typedef Node* NodePointer;

class Matrix {

private:
	//TODO - Representation
	int nr_lines;
	int nr_columns;
	NodePointer* hashTable;
	int m;
	int n;

	//hash function
	int h(TElem e);
	void resize();
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	int numberOfNonZeroElems(int col) const;

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

};
