#pragma once
#include "Event.h"
#include <vector>
#include <fstream>

class UserList
{
protected:
	std::vector<Event> events;
	int current;

public:
	UserList();
	size_t get_size();

	std::vector<Event> get_events();
	Event get_current_event();
	bool is_empty();
	void add(Event event);
	int delete_event(Event event);
	void go_to_next();

	void change_number_of_people_user_list(Event event);

	void open_site();

};

