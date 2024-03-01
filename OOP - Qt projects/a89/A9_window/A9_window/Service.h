#pragma once
#include "Repository.h"
#include "UserList.h"
#include "FileRepository.h"
#include "FileUserList.h"
#include "Validator.h"
#include <string>
#include <vector>
#include <algorithm>

class Service
{
private:
	FileRepository repository;
	FileUserList* user_list;
	Validator validator;

public:
	Service();
	Service(const FileRepository repository, FileUserList* userlist) : repository(repository), user_list(userlist) {}

	void save_to_file();
	void open_the_file();

	// Passes the new event to the repository
	void add_event_to_repository(const std::string the_new_title, const std::string the_new_description, const int the_new_date_time, const int the_new_number_of_people, const std::string the_new_link);
	// Passes the title of the event to delete
	void delete_event_from_repository(const std::string title);
	// Passes the event with the updated elements
	void update_event_from_repository(const std::string the_new_title, const std::string the_new_description, const int the_new_date_time, const int the_new_number_of_people, const std::string the_new_link);

	// Returns all the events from the repository
	std::vector<Event> get_all_events();

	// Input: the month; it returns a UserList with events in the given month
	UserList get_events_for_given_month(std::string month);
	// Adds the input event in the user_list
	void add_event_to_user_list(Event event);
	// Deletes the input event from the user_list
	void delete_event_from_user_list(std::string title);

	// Returns the user_list
	std::vector<Event> get_user_list();

};

