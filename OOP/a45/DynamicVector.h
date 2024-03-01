#pragma once

template <typename T>
class DynamicVector
{
private:
	T* elements;
	int size;
	int capacity;

public:
	// default constructor for a DynamicVector
	DynamicVector(int capacity = 10);

	// copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& vector);

	// destructor
	~DynamicVector();

	// assignment operator for a DynamicVector
	DynamicVector& operator=(const DynamicVector& vector);

	// adds an element to the current DynamicVector
	void add_item(const T& element);

	// deletes an element from the current DynamicVector
	void delete_item(const int positon);

	// updates an element in the current DynamicVector
	void update_item(const int position, const T element);

	// a reference to the element of given position
	T operator[](int position);

	// gets the size of the array
	int get_size() const;

	T get_element(const int position) const;


private:
	// resizes the current DynamicVector, multiplying its capacity by a given factor
	void resize(int factor = 2);
};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new T[capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& vector)
{
	this->size = vector.size;
	this->capacity = vector.capacity;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = vector.elements[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elements;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& vector)
{
	if (this == &vector)
		return *this;

	this->size = vector.size;
	this->capacity = vector.capacity;

	delete[] this->elements;
	this->elements = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = vector.elements[i];

	return *this;
}

template <typename T>
void DynamicVector<T>::add_item(const T& element)
{
	if (this->size == this->capacity)
		this->resize();
	this->elements[this->size] = element;
	this->size++;
}

template<typename T>
void DynamicVector<T>::delete_item(const int position)
{
	int index = 0;
	T* the_new_array = new T[this->capacity];
	for (int i = 0; i < this->size && index < this->size; i++)
	{
		if (index == position)
			index++;
		if (index < this->size)
			the_new_array[i] = this->elements[index];
		index++;
	}
	delete[] this->elements;
	this->elements = the_new_array;
	this->size--;
}

template<typename T>
inline void DynamicVector<T>::update_item(const int position, const T element)
{
	this->elements[position] = element;
}

template <typename T>
void DynamicVector<T>::resize(int factor)
{
	this->capacity *= factor;

	T* the_new_array = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		the_new_array[i] = this->elements[i];

	delete[] this->elements;
	this->elements = the_new_array;
}

template <typename T>
T DynamicVector<T>::operator[](int position)
{
	return this->elements[position];
}

template <typename T>
int DynamicVector<T>::get_size() const
{
	return this->size;
}

template <typename T>
T DynamicVector<T>::get_element(const int position) const
{
	return this->elements[position];
}

