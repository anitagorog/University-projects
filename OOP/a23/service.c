#include "service.h"

DynamicArray sort_the_chosen_estates(DynamicArray list_of_estates)
{
    int its_not_sorted_yet = 1;
    while (its_not_sorted_yet == 1)
    {
        its_not_sorted_yet = 0;
        for (int i = 0; i < list_of_estates.length - 1; i++)
        {
            if (list_of_estates.elems[i].price > list_of_estates.elems[i + 1].price)
            {
                Estate the_estate_used_for_exchange;
                the_estate_used_for_exchange = list_of_estates.elems[i];
                list_of_estates.elems[i] = list_of_estates.elems[i + 1];
                list_of_estates.elems[i + 1] = the_estate_used_for_exchange;

                its_not_sorted_yet = 1;
            }
        }
    }
    return list_of_estates;
}

DynamicArray make_the_estates_containing_a_given_string(char string_to_search_for[], DynamicArray list_of_estates)
{
    DynamicArray* the_estates_containing_the_given_string = createDynamicArray(20);
    for (int i = 0; i < list_of_estates.length; i++)
    {
        if (strstr(list_of_estates.elems[i].address, string_to_search_for) != 0)
        {
            add(the_estates_containing_the_given_string, list_of_estates.elems[i]);
        }
    }
    sort_the_chosen_estates(*the_estates_containing_the_given_string);
}

DynamicArray estates_of_a_given_type_having_the_surface_greater_than_a_value(char string_to_search_for[], int the_value, DynamicArray list_of_estates)
{
    DynamicArray* the_estates_fulfilling_the_given_type_and_surface = createDynamicArray(20);
    for (int i = 0; i < list_of_estates.length; i++)
    {
        if (strcmp(list_of_estates.elems[i].type, string_to_search_for) == 0 && list_of_estates.elems[i].surface > the_value)
        {
            add(the_estates_fulfilling_the_given_type_and_surface, list_of_estates.elems[i]);
        }
    }
    return *the_estates_fulfilling_the_given_type_and_surface;
}

void undo(DynamicArray* list_of_estates, DynamicArray array_undo[], int number_of_changes)
{
    *list_of_estates = array_undo[number_of_changes - 1];
}

void redo(DynamicArray* list_of_estates, DynamicArray array_redo[], int number_of_changes)
{
    *list_of_estates = array_redo[number_of_changes];
}

void tests_service()
{
    DynamicArray* test_array = createDynamicArray(20);

    Estate estate_1;
    estate_1.price = 4;
    estate_1.surface = 7;
    strcpy(estate_1.address, "Addres1");
    strcpy(estate_1.type, "house");
    add(test_array, estate_1);
    assert(getLength(test_array) == 1);

    Estate estate_2;
    estate_1.price = 1;
    estate_1.surface = 7;
    strcpy(estate_1.address, "Addres2");
    strcpy(estate_1.type, "house");
    add(test_array, estate_1);
    assert(getLength(test_array) == 2);

    sort_the_chosen_estates(*test_array);
    assert(test_array->elems[0].price == 1);

    make_the_estates_containing_a_given_string("2", *test_array);
    assert(test_array->elems[0].price == 1);

    DynamicArray* new_test_array = createDynamicArray(20);
    *new_test_array = estates_of_a_given_type_having_the_surface_greater_than_a_value("house", 8, *test_array);
    assert(getLength(new_test_array) == 0);

    destroy(new_test_array);
    destroy(test_array);
}
