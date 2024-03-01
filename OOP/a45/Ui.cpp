#include "Ui.h"
#include <string>
#include <iostream>
#include <windows.h>

void Ui::run_program()
{
	while (true)
	{
		print_menu();
		std::string command;
		std::getline(std::cin, command);
		if (command == "exit")
		{	
			break;
		}
		else if (command == "admin")
		{
			run_admin_mode();
		}
		else if (command == "user")
		{
			run_user_mode();
		}
		else
			std::cout << "Invalid mode\n";
	}
}

void Ui::run_admin_mode()
{
	while (true)
	{
		print_menu_admin();
		std::string command;
		std::getline(std::cin, command);
		if (command == "exit")
		{
			break;
		}
		if (command == "add")
		{
			add_event_to_array();
			std::cout << '\n';
			continue;
		}
		if (command == "delete")
		{
			delete_event_from_array();
			std::cout << '\n';
			continue;
		}
		if (command == "update")
		{
			update_event_in_array();
			std::cout << '\n';
			continue;
		}
		if (command == "list")
		{
			list_all_events();
			std::cout << '\n';
			continue;
		}
		std::cout << "Invalid command\n\n";
	}
}

void Ui::run_user_mode()
{
	while (true)
	{
		print_menu_user();
		std::string command;
		std::getline(std::cin, command);
		if (command == "exit")
		{
			break;
		}
		if (command == "see")
		{
			make_list_for_user();
			std::cout << '\n';
			continue;
		}
		if (command == "delete")
		{
			delete_event_from_user_list();
			std::cout << '\n';
			continue;
		}
		if (command == "list")
		{
			print_list_made_by_user(this->service.get_user_list());
			std::cout << '\n';
			continue;
		}
		std::cout << "Invalid command\n\n";
	}
}

void Ui::print_menu()
{
	std::cout << "\nPlease select your mode from: admin / user\nOr exit\n";
}

void Ui::print_menu_admin()
{
	std::cout << "\nadd - Add an event\n";
	std::cout << "delete - Delete an event\n";
	std::cout << "update - Update an event\n";
	std::cout << "list - List all events\n";
	std::cout << "exit\n";
}

void Ui::print_menu_user()
{
	std::cout << "\nsee - See events for a given month\n";
	std::cout << "delete - Delete an event from my list\n";
	std::cout << "list - List my events\n";
	std::cout << "exit\n";
}

void Ui::add_event_to_array()
{
	std::string the_title, the_description, the_date_time, the_number_of_people, the_link;
	std::cout << "Write the title: ";
	std::getline(std::cin, the_title);
	std::cout << "Write the description: ";
	std::getline(std::cin, the_description);
	std::cout << "Write the date and time: ";
	std::getline(std::cin, the_date_time);
	std::cout << "Write the number of people: ";
	std::getline(std::cin, the_number_of_people);
	std::cout << "Write the link: ";
	std::getline(std::cin, the_link);
	for (char const& ch : the_date_time)
	{
		if (std::isdigit(ch) == 0) {
			std::cout << "Date supposed to be a number";
			return;
		}
	}
	for (char const& ch : the_number_of_people)
	{
		if (std::isdigit(ch) == 0) {
			std::cout << "Number of people supposed to be a number";
			return;
		}
	}
	if (the_date_time.size() != 8)
		std::cout << "Not valid date";
	else 
		this->service.add_event_to_repository(the_title, the_description, stoi(the_date_time), stoi(the_number_of_people), the_link);
}

void Ui::delete_event_from_array()
{
	std::string title;
	std::cout << "Write the title: ";
	std::getline(std::cin, title);

	this->service.delete_event_from_repository(title);
}

void Ui::update_event_in_array()
{
	std::string title, the_new_description, the_new_date_time, the_new_number_of_people, the_new_link;
	std::cout << "Write the title of the event you would like to update: ";
	std::getline(std::cin, title);
	std::cout << "Write the new description: ";
	std::getline(std::cin, the_new_description);
	std::cout << "Write the new date time: ";
	std::getline(std::cin, the_new_date_time);
	std::cout << "Write the new number of people: ";
	std::getline(std::cin, the_new_number_of_people);
	std::cout << "Write the new link: ";
	std::getline(std::cin, the_new_link);

	this->service.update_event_from_repository(title, the_new_description, stoi(the_new_date_time), stoi(the_new_number_of_people), the_new_link);
}

void Ui::list_all_events()
{
	DynamicVector<Event> list = this->service.get_all_events();
	Event event;
	for (int i = 0; i < list.get_size(); i++)
	{
		event = list.get_element(i);
		std::cout << "Event title: " << event.get_title() << " description: " << event.get_description() << " date/time: " << event.get_the_date_time() << " number of people who will attend: " << event.get_the_number_of_people() << " and link: " << event.get_the_link() << "\n";
	}
}

void Ui::make_list_for_user()
{
	std::cout << "Add a month (its number): ";
	std::string month;
	std::getline(std::cin, month);
	for (char const& ch : month)
	{
		if (std::isdigit(ch) == 0) {
			std::cout << "Month supposed to be a number";
			return;
		}
	}
	UserList the_list_with_given_month_selected_by_user = this->service.get_events_for_given_month(month);
	Event event;
	std::string command;
	while (!the_list_with_given_month_selected_by_user.is_empty())
	{
		print_menu_for_making_user_list();
		the_list_with_given_month_selected_by_user.open_site();
		event = the_list_with_given_month_selected_by_user.get_current_event();
		std::cout << "Event title: " << event.get_title() << " description: " << event.get_description() << " date/time: " << event.get_the_date_time() << " number of people who will attend: " << event.get_the_number_of_people() << " and link: " << event.get_the_link() << "\n\n";
		std::getline(std::cin, command);
		if (command == "exit")
			break;
		if (command == "add")
		{
			this->service.add_event_to_user_list(event);
			the_list_with_given_month_selected_by_user.delete_event(event);
		}
		if (command == "next")
			the_list_with_given_month_selected_by_user.go_to_next();
	}
	if (the_list_with_given_month_selected_by_user.is_empty())
		std::cout << "No more events\n";

}

void Ui::print_menu_for_making_user_list()
{
	std::cout << "\nnext - Skip the current event\n";
	std::cout << "add - Add the current event to your list\n";
	std::cout << "exit\n";
}

void Ui::print_list_made_by_user(UserList list)
{
	if (list.is_empty())
	{
		std::cout << "No event in your list!\n";
		return;
	}
	Event event;
	for (int i = 0; i < list.get_size(); i++)
	{
		event = list.get_current_event();
		std::cout << "Event title: " << event.get_title() << " description: " << event.get_description() << " date/time: " << event.get_the_date_time() << " number of people who will attend: " << event.get_the_number_of_people() << " and link: " << event.get_the_link() << "\n";
		list.go_to_next();
	}
}

void Ui::delete_event_from_user_list()
{
	std::string title;
	std::cout << "Insert the title of the event you would like to delete: ";
	std::getline(std::cin, title);

	this->service.delete_event_from_user_list(title);
}

