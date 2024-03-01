#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Domain.h"
#include "Repository.h"
#include "service.h"

void start_app();

void print_the_menu();

int check_if_address_is_unique(char address[], DynamicArray list_of_estates);

Estate Read_an_estate(DynamicArray list_of_estates);

void print_all_estates(DynamicArray list_of_estates);

void menu_for_choosing_what_to_update();

int reading_command_until_valid_input(char options[]);

int reading_until_input_is_a_number();

void make_random_10_element(DynamicArray* list_of_estates);
