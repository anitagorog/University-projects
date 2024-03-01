#include "UserList.h"

UserList::UserList()
{
	current = 0;
}

int UserList::get_size()
{
	return events.get_size();
}

Event UserList::get_current_event()
{
	return this->events.get_element(this->current);
}

bool UserList::is_empty()
{
	if (this->events.get_size() == 0)
		return true;
	return false;
}

void UserList::add(Event event)
{
	this->events.add_item(event);
}

int UserList::delete_event(Event event)
{
	int position_of_event = find_event(event);
	if (position_of_event != -1)
	{
		this->events.delete_item(position_of_event);
		return 1;
	}
	return 0;
}

int UserList::find_event(Event event)
{
	for (int i = 0; i < this->events.get_size(); i++)
		if (this->events.get_element(i).get_title() == event.get_title())
			return i;
	return -1;
}

void UserList::go_to_next()
{
	if (current + 1 == this->events.get_size())
	{
		this->current = 0;
	}
	else
		current++;
}

void UserList::change_number_of_people_user_list(Event event)
{
	int position = this->find_event(event);
	Event new_event = Event(event.get_title(), event.get_description(), event.get_the_date_time(), event.get_the_number_of_people() + 1, event.get_the_link());
	events.delete_item(position);
	events.add_item(new_event);
}

void UserList::open_site()
{
	if (this->events.get_size() == 0)
		return;
	Event current_event = this->get_current_event();
	current_event.open_the_site();
}


