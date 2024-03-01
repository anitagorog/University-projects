#pragma once
#include "Domain.h"
#include <assert.h>

typedef Estate TElement;

typedef struct
{
	TElement* elems;
	int length;
	int capacity;
} DynamicArray;

/// <summary>
/// Creates a dynamic array of generic elements, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <returns>A pointer the the created dynamic array.</returns>
DynamicArray* createDynamicArray(int capacity);

/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="array">The dynamic array to be destoyed.</param>
/// <returns>A pointer the the created dynamic array.</returns>
void destroy(DynamicArray* array);

/// <summary>
/// Adds a generic element to the dynamic array.
/// </summary>
/// <param name="array">The dynamic array.</param>
/// <param name="p">The planet to be added.</param>
void add(DynamicArray* array, TElement estate);

/// <summary>
/// Resizes the array in case of too many elements
/// </summary>
/// <param name="array">The dynamic array</param>
void resize(DynamicArray* array);

/// <summary>
/// Gets length of dynamic array
/// </summary>
/// <param name="array">The array</param>
/// <returns>the length</returns>
int getLength(DynamicArray* array);

/// <summary>
/// Gets capacity of dynamic array
/// </summary>
/// <param name="array">The array</param>
/// <returns>the capacity</returns>
int getCapacity(DynamicArray* array);

/// <summary>
/// Deletes an estate from the dynamic array
/// </summary>
/// <param name="address_to_remove">The address of the estate to remove</param>
/// <param name="list_of_estates">The array</param>
void delete_the_estate(char address_to_remove[], DynamicArray* list_of_estates);

/// <summary>
/// Updates an estate by type or address
/// </summary>
/// <param name="address_to_update">The adress of the estate</param>
/// <param name="list_of_estates">The array</param>
/// <param name="intention">Change type or address</param>
/// <param name="new_element">New type or address</param>
void update_an_estate_by_type_or_address(char address_to_update[], DynamicArray* list_of_estates, int intention, char new_element[]);

/// <summary>
/// Updates an estate by price or surface
/// </summary>
/// <param name="address_to_update">The adress of the estate</param>
/// <param name="list_of_estates">The array</param>
/// <param name="intention">Change price or surface</param>
/// <param name="new_element">New price or surface</param>
void update_an_estate_by_price_or_surface(char address_to_update[], DynamicArray* list_of_estates, int intention, int new_element);

//void test_repository();
