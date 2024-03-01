// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

void the_menu()
{
    //Menu
    printf("\n1. Read a vector of numbers\n");
    printf("2. Generate the first n prime numbers (n is a given natural number)\n");
    printf("3. Given a vector of numbers, find the longest contiguous subsequence such that any two consecutive elements are \n relatively prime\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

int is_prime(int the_number_to_check)
{
    //Checks if the number the_nr_to_check is prime; if it is returns 1, otherwise returns -1
    for (int i = 2; i < the_number_to_check; i++)
    {
        if (the_number_to_check % i == 0)
        {
            return -1;
        }
    }
    return 1;
}

void generate_primes_less_than(int maximum_value)
{
    //Generates and prints all the prime numbers from 1 to the number maximum_value
    for (int i = 2; i <= maximum_value; i++)
    {
        if ((i == 2) || is_prime(i) != -1)
        {
            printf("%d ", i);
        }
    }
}

void read_the_vector(int *v, int number_elements)
{
    //Reads a vector of number_elements elements
    for (int i = 0; i < number_elements; i++)
    {
        printf("Vector[%d]= ", i);
        scanf_s("%d", &v[i]);
    }
}

int minimum(int first_nr, int second_nr)
{
    //Returns the smaller value between first_nr and second_nr
    if (first_nr > second_nr)
        return second_nr;
    return first_nr;
}

int is_relatively_prime(int first_nr, int second_nr)
{
    //Checks if first_nr and second_nr are relatively prime; if they are returns 1, otherwise -1
    for (int i = 2; i < minimum(first_nr, second_nr); i++)
        if (first_nr % i == 0 && second_nr % i == 0)
            return -1;
    return 1;
}

void longest_contiguous_subsequence_such_that_any_two_consecutive_elements_are_relatively_prime(
    int *vector, int n, int *max_len, int *max_ind)
{
    //Finds the longest contiguous subsequence with the given criteria in the vector
    int starting_index = 0, length = 0, max_length = 0, max_index = 0;
    for (int i = 0; i < (n - 1); i++)
    {
        if (is_relatively_prime(vector[i], vector[i + 1]) == 1)
        {
            if (length == 0)
            {
                length = 2;
                starting_index = i;
            }
            else length += 1;
        }
        else 
            length = 0;
        if (max_length < length)
        {
            max_length = length;
            max_index = starting_index;
        }
    }
    *max_len = max_length;
    *max_ind = max_index;
}

int main()
{
    int choice, the_given_number_n;
    int number_of_elements=0;
    int vector[100];
    while (1)
    {
        the_menu();
        scanf_s("%d", &choice);
        if (choice == 1)
        {
            printf("Choose the number of elements of the vector: ");
            scanf_s("%d", &number_of_elements);
            read_the_vector(vector,number_of_elements);
            printf("Your vector: ");
            for (int i = 0; i < number_of_elements; i++)
            {
                printf("%d ", vector[i]);
            }
        }
        else if (choice == 2)
        {
            printf("Choose the number n=? >>> ");
            scanf_s("%d", &the_given_number_n);
            generate_primes_less_than(the_given_number_n);
        }
        else if (choice == 3)
        {
            int max_len = 0, index = 0;
            if (number_of_elements == 0)
                printf("Please first read a vector");
            else
            {
                longest_contiguous_subsequence_such_that_any_two_consecutive_elements_are_relatively_prime(vector, number_of_elements, &max_len, &index);
                printf("The longest subsequence like that: ");
                for (int i = index; i < (index + max_len); i++)
                {
                    printf("%d ", vector[i]);
                }
            }     
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            printf("Invalid request");
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
