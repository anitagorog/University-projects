#pragma once
#include "Domain.h"
#include "Repository.h"
#include "UI.h"
#include <string.h>

/// <summary>
/// Sort the elements of a dynamic array
/// </summary>
/// <param name="list_of_estates">The array</param>
/// <returns>The sorted dynamic array</returns>
DynamicArray sort_the_chosen_estates(DynamicArray list_of_estates);

/// <summary>
/// Makes a new array whose estates adresses' contain a user chosen string
/// </summary>
/// <param name="string_to_search_for">The string</param>
/// <param name="list_of_estates">The array</param>
/// <returns>New array</returns>
DynamicArray make_the_estates_containing_a_given_string(char string_to_search_for[], DynamicArray list_of_estates);

/// <summary>
/// Makes a new array containing estates of a given type and surface
/// </summary>
/// <param name="string_to_search_for">The string</param>
/// <param name="the_value">The value from which the surface should be greater</param>
/// <param name="list_of_estates">The array</param>
/// <returns>The new array</returns>
DynamicArray estates_of_a_given_type_having_the_surface_greater_than_a_value(char string_to_search_for[], int the_value, DynamicArray list_of_estates);

/// <summary>
/// Undoes the last action
/// </summary>
/// <param name="list_of_estates">The array</param>
/// <param name="array_undo_redo">An array containing the changed arrays</param>
/// <param name="number_of_changes">integer</param>
void undo(DynamicArray* list_of_estates, DynamicArray array_undo[], int number_of_changes);

/// <summary>
/// Redoes the last action
/// </summary>
/// <param name="list_of_estates">The array</param>
/// <param name="array_undo_redo">An array containing the changed arrays</param>
/// <param name="number_of_changes">integer</param>
void redo(DynamicArray* list_of_estates, DynamicArray array_redo[], int number_of_changes);

void tests_service();
