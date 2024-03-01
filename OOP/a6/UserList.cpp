#include "UserList.h"

UserList::UserList()
{
	current = 0;
}

size_t UserList::get_size()
{
	return events.size();
}

std::vector<Event> UserList::get_events()
{
	return this->events;
}

Event UserList::get_current_event()
{
	return this->events[this->current];
}

bool UserList::is_empty()
{
	if (this->events.size() == 0)
		return true;
	return false;
}

void UserList::add(Event event)
{
	this->events.push_back(event);
}

int UserList::delete_event(Event event)
{
	std::string title = event.get_title();
	auto lambda = [title](Event event_from_list) {return bool(event_from_list.get_title() == title); };
	auto position_of_event = std::find_if(events.begin(), events.end(), lambda);
	if (position_of_event != this->events.end())
	{
		this->events.erase(position_of_event);
		return 1;
	}
	return 0;
}

void UserList::go_to_next()
{
	if (current + 1 == this->events.size())
	{
		this->current = 0;
	}
	else
		current++;
}

void UserList::change_number_of_people_user_list(Event event)
{
	auto position = find(this->events.begin(), this->events.end(), event);
	Event new_event = Event(event.get_title(), event.get_description(), event.get_the_date_time(), event.get_the_number_of_people() + 1, event.get_the_link());
	events.erase(position);
	events.push_back(new_event);
}

void UserList::open_site()
{
	if (this->events.size() == 0)
		return;
	Event current_event = this->get_current_event();
	current_event.open_the_site();
}


