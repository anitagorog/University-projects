#include "Repository.h"
#include <stdlib.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* dynamic_array_of_estates = malloc(sizeof(DynamicArray));
	// make sure that the space was allocated
	if (dynamic_array_of_estates == NULL)
		return NULL;

	dynamic_array_of_estates->capacity = capacity;
	dynamic_array_of_estates->length = 0;

	// allocate space for the elements
	dynamic_array_of_estates->elems = malloc(capacity * sizeof(TElement));
	if (dynamic_array_of_estates->elems == NULL)
		return NULL;

	return dynamic_array_of_estates;
}

void destroy(DynamicArray* the_array)
{
	if (the_array == NULL)
		return;

	// free the space allocated for the planets
	free(the_array->elems);
	the_array->elems = NULL;

	// free the space allocated for the dynamic array
	free(the_array);
	//arr = NULL; // !!!
}

void resize(DynamicArray* array)
{
	if (array == NULL)
		return;

	array->capacity *= 2;
	TElement* aux = realloc(array->elems, array->capacity * sizeof(TElement));
	if (aux == NULL)
		return; // array cannot be resized (TODO - return error code and check when resizing)
	array->elems = aux;
}

void add(DynamicArray* array, TElement estate)
{
	if (array == NULL)
		return;
	if (array->elems == NULL)
		return;

	// resize the array, if necessary
	if (array->length == array->capacity)
		resize(array);
	array->elems[array->length] = estate;
	array->length++;
}

int getLength(DynamicArray* array)
{
	if (array == NULL)
		return 0;
	return array->length;
}

int getCapacity(DynamicArray* array)
{
	if (array == NULL)
		return 0;
	return array->capacity;
}

void delete_the_estate(char address_to_remove[], DynamicArray* list_of_estates)
{
	int number_of_found_estates_with_that_address = 0;

	for (int i = 0; i < list_of_estates->length; i++)
		if (strcmp(list_of_estates->elems[i].address, address_to_remove) == 0)
			for (int j = i; j < list_of_estates->length - 1; j++)
			{
				strcpy(list_of_estates->elems[j].address, list_of_estates->elems[j + 1].address);
				strcpy(list_of_estates->elems[j].type, list_of_estates->elems[j + 1].type);
				list_of_estates->elems[j].price = list_of_estates->elems[j + 1].price;
				list_of_estates->elems[j].surface = list_of_estates->elems[j + 1].surface;
				number_of_found_estates_with_that_address += 1;
			}
	if (strcmp(list_of_estates->elems[list_of_estates->length - 1].address, address_to_remove) == 0)
		number_of_found_estates_with_that_address += 1;

	list_of_estates->length -= number_of_found_estates_with_that_address;
}

void update_an_estate_by_type_or_address(char address_to_update[], DynamicArray* list_of_estates, int intention, char new_element[])
{
	for (int i = 0; i < list_of_estates->length; i++)
		if (strcmp(list_of_estates->elems[i].address, address_to_update) == 0)
		{
			if (intention == 1)
			{
				strcpy(list_of_estates->elems[i].type, new_element);
			}
			else if (intention == 2)
			{
				strcpy(list_of_estates->elems[i].address, new_element);
			}
		}
}

void update_an_estate_by_price_or_surface(char address_to_update[], DynamicArray* list_of_estates, int intention, int new_element)
{
	for (int i = 0; i < list_of_estates->length; i++)
		if (strcmp(list_of_estates->elems[i].address, address_to_update) == 0)
		{
			if (intention == 3)
			{
				list_of_estates->elems[i].surface = new_element;
			}
			else if (intention == 4)
			{
				list_of_estates->elems[i].price = new_element;
			}
		}
}

void test_repository()
{
	DynamicArray* test_array = createDynamicArray(20);
	if (test_array == NULL)
		assert(0);
	assert(getCapacity(test_array) == 20);
	assert(getLength(test_array) == 0);

	Estate estate_1; 
	estate_1.price = 1;
	estate_1.surface = 7;
	strcpy(estate_1.address, "Addres1");
	strcpy(estate_1.type, "house");
	add(test_array, estate_1);
	assert(getLength(test_array) == 1);

	update_an_estate_by_type_or_address("Addres1", test_array, 1, "penthouse");
	assert(strcmp(test_array->elems[0].type, "penthouse") == 0);

	update_an_estate_by_price_or_surface("Addres1", test_array, 3, 99);
	assert(test_array->elems[0].surface == 99);

	delete_the_estate("Addres1", test_array);
	assert(getLength(test_array) == 0);

	destroy(test_array);
}
