#include "UI.h"

void print_the_menu()
{
	printf("\nChoose your intention:\n0. Exit\n1. Add, delete or update an estate. An estate is uniquely identified by its address.\n");
	printf("2. Display all estates whose address contains a given string(if the string is empty, all estates will be considered), sorted ascending by their price.\n");
	printf("3. See all estates of a given type, having the surface greater than a user provided value.\n");
	printf("4. Provide multiple undo and redo functionality. Each step will undo/redo the previous operation performed by the user.\n");
}

int choose_the_type()
{
	int chosen = 0;
	int the_type;
	char options[] = "123";
	printf("\n1. House\n2. Apartment\n3. Penthouse\n");
	the_type = reading_command_until_valid_input(options);
	return the_type;
}

int check_if_address_is_unique(char address[], DynamicArray list_of_estates)
{
	for (int i = 0; i < list_of_estates.length; i++)
	{
		if (strcmp(list_of_estates.elems[i].address, address) == 0)
		{
			printf("Address already existing\n");
			return 1;
		}
	}
	return 0;
}

Estate Read_an_estate(DynamicArray list_of_estates)
{
	Estate estate;
	char type_to_add[50];
	char address_to_add[50];
	int surface_to_add;
	int price_to_add;

	printf("The type of the estate to add: ");
	int the_number_of_type = choose_the_type();
	if (the_number_of_type == 1)
		strcpy(type_to_add, "house");
	else if (the_number_of_type == 2)
		strcpy(type_to_add, "apartment");
	else
		strcpy(type_to_add, "penthouse");

	printf("The address of the estate to add: ");
	int address_is_unique = 1;
	while (address_is_unique == 1)
	{
		scanf("%s", address_to_add);
		address_is_unique = check_if_address_is_unique(address_to_add, list_of_estates);
	}

	printf("The surface of the estate to add: ");
	surface_to_add = reading_until_input_is_a_number();
	printf("The price of the estate to add: ");
	price_to_add = reading_until_input_is_a_number();

	estate.price = price_to_add;
	estate.surface = surface_to_add;
	strcpy(estate.type, type_to_add);
	strcpy(estate.address, address_to_add);
	return estate;
}

void print_all_estates(DynamicArray list_of_estates)
{
	printf("\nThe list of estates:\n");
	for (int i = 0; i < list_of_estates.length; i++)
		printf("%s %s %d %d\n", list_of_estates.elems[i].type, list_of_estates.elems[i].address, list_of_estates.elems[i].surface, list_of_estates.elems[i].price);
}

void menu_for_choosing_what_to_update()
{
	printf("\nWhich would you like to update:\n1. Type\n2. Address\n3. Surface\n4. Price\n");
}

int reading_command_until_valid_input(char options[])
{
	char input[20];
	int number_input;
	scanf("%s", input);
	while (strstr(options, input) == NULL)
	{
		printf("Wrong input, please try again\n");
		scanf("%s", input);
	}
	number_input = atoi(input);
	return number_input;
}

int reading_until_input_is_a_number()
{
	char string_of_numbers[] = "1234567890";
	char input[20];
	int number_input;
	int it_is_number = 1;
	while (it_is_number == 1)
	{
		it_is_number = 0;
		scanf("%s", input);
		if (strlen(input) == 1)
		{
			if (strstr(string_of_numbers, input) == NULL)
			{
				printf("Wrong input, please try again\n");
				it_is_number = 1;
			}
		}
		else
		{
			for (int i = 0; i < strlen(input); i++)
			{
				if (strchr(string_of_numbers, input[i]) == NULL)
				{
					printf("Wrong input, please try again\n");
					it_is_number = 1;
				}
			}
		}
	}
	number_input = atoi(input);
	return number_input;
}

void make_random_10_element(DynamicArray* list_of_estates)
{
	for (int i = 0; i < 10; i++)
	{
		Estate t;
		strcpy(t.type, "house");
		char address[20] = "Main_street_";
		char number_address = i + '0';
		int len = strlen(address);
		address[len] = number_address;
		address[len+1] = '\0';
		strcpy(t.address, address);
		t.surface = i * 3+1;
		t.price = i * 2+1;
		add(list_of_estates, t);
	}
}

void start_app()
{
	DynamicArray* Estates = createDynamicArray(20);
	DynamicArray array_undo[100];
	DynamicArray array_redo[100];
	int number_of_changes = 0, number_of_undos = 0;
	make_random_10_element(Estates);
	print_all_estates(*Estates);

	while (1)
	{
		int command;
		print_the_menu();
		char options[] = "01234";
		command = reading_command_until_valid_input(options);

		switch (command)
		{
		case 0:
			destroy(Estates);
			return;
			break;
		case 1:
		{
			array_undo[number_of_changes] = *Estates;
			number_of_changes += 1;

			int choice_of_add_delete_or_update;
			printf("Which do you intend:\n1. Add\n2. Delete\n3. Update\n");
			scanf_s("%d", &choice_of_add_delete_or_update);
			if (choice_of_add_delete_or_update == 1)
			{
				Estate t = Read_an_estate(*Estates);
				add(Estates, t);
				print_all_estates(*Estates);
			}
			else if (choice_of_add_delete_or_update == 2)
			{
				char the_address_to_remove[50];
				printf("Enter the address: ");
				scanf("%s", the_address_to_remove);
				delete_the_estate(the_address_to_remove, Estates);
				print_all_estates(*Estates);
			}
			else if (choice_of_add_delete_or_update == 3)
			{
				char the_address_of_the_estate_to_update[50];
				menu_for_choosing_what_to_update();
				int intention;
				scanf("%d", &intention);
				printf("Enter the address: ");
				scanf("%s", the_address_of_the_estate_to_update);
				if (intention == 1)
				{
					char new_type[50];
					printf("The new type: ");
					int the_number_of_type;
					the_number_of_type = choose_the_type();
					if (the_number_of_type == 1)
						strcpy(new_type, "house");
					else if (the_number_of_type == 2)
						strcpy(new_type, "apartment");
					else
						strcpy(new_type, "penthouse");
					update_an_estate_by_type_or_address(the_address_of_the_estate_to_update, Estates, intention, new_type);
				}
				else if (intention == 2)
				{
					char new_address[50];
					printf("The new address: ");
					scanf("%s", new_address);
					update_an_estate_by_type_or_address(the_address_of_the_estate_to_update, Estates, intention, new_address);
				}
				else if (intention == 3)
				{
					int new_surface;
					printf("The new surface: ");
					new_surface = reading_until_input_is_a_number();
					update_an_estate_by_price_or_surface(the_address_of_the_estate_to_update, Estates, intention, new_surface);
				}
				else if (intention == 4)
				{
					int new_price;
					printf("The new price: ");
					new_price = reading_until_input_is_a_number();
					update_an_estate_by_price_or_surface(the_address_of_the_estate_to_update, Estates, intention, new_price);
				}
				else
					return;
				print_all_estates(*Estates);
			}
			else
			{
				printf("Invalid request\n");
			}
			break;
		}
		case 2:
		{
			printf("Type what are you searching for: ");
			char string_to_search_for[50];
			scanf("%s", string_to_search_for);
			print_all_estates(make_the_estates_containing_a_given_string(string_to_search_for, *Estates));
			break;
		}
		case 3:
		{
			printf("The type: ");
			char the_type_user_searches_for[20];
			scanf("%s", the_type_user_searches_for);
			printf("The value for the surface greater than: ");
			int the_value_user_chooses;
			scanf("%d", &the_value_user_chooses);
			print_all_estates(estates_of_a_given_type_having_the_surface_greater_than_a_value(the_type_user_searches_for, the_value_user_chooses, *Estates));
			break;
		}
		case 4:
		{
			printf("Which? undo/redo >>> ");
			char undo_or_redo[10];
			scanf("%s", undo_or_redo);
			if (strcmp(undo_or_redo, "undo") == 0 && number_of_changes >= 1)
			{
				array_redo[number_of_undos] = *Estates;
				number_of_undos += 1;

				undo(Estates, array_undo, number_of_changes);
				number_of_changes -= 1;
				print_all_estates(*Estates);
			}
			else if (strcmp(undo_or_redo, "redo") == 0 && number_of_undos >= 1)
			{
				redo(Estates, array_redo, number_of_changes);
				number_of_undos -= 1;
				print_all_estates(*Estates);
			}
			else
				printf("Invalid request");
			break;
		}
		default:
		{
			printf("Invalid request");
			break;
		}
		}
	}
}
