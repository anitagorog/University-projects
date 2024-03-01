#pragma once
#include "Event.h"
#include "DynamicVector.h"

class UserList
{
private:
	DynamicVector<Event> events;
	int current;

public:
	UserList();
	int get_size();

	Event get_current_event();
	bool is_empty();
	void add(Event event);
	int delete_event(Event event);
	int find_event(Event event);
	void go_to_next();

	void change_number_of_people_user_list(Event event);

	void open_site();

};

