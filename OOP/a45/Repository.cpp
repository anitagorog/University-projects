#include "Repository.h"

void Repository::add_event(const Event event)
{
	int position = find_event(event.get_title());
	if (position == -1)
		this->events.add_item(event);
	else
		std::cout << "Duplicate event\n";
}

void Repository::delete_event(const Event event)
{
	int position = find_event(event.get_title());
	if (position == -1)
		std::cout << "Event not found\n";
	else
		this->events.delete_item(position);
		
}

void Repository::update_event(const Event event)
{
	int position = find_event(event.get_title());
	if (position == -1)
		std::cout << "Event not found\n";
	else
		this->events.update_item(position, event);
}

int Repository::find_event(const std::string title_to_look_for)
{
	Event the_event_to_search_for;
	for (int i = 0; i < this->events.get_size(); i++)
	{
		the_event_to_search_for = this->events.get_element(i);
		if (the_event_to_search_for.get_title() == title_to_look_for)
			return i;
	}
	return -1;
}

void Repository::increase_number_of_people(Event event)
{
	int position = this->find_event(event.get_title());
	Event new_event = Event(event.get_title(), event.get_description(), event.get_the_date_time(), event.get_the_number_of_people() + 1, event.get_the_link());
	events.delete_item(position);
	events.add_item(new_event);
}

void Repository::decrease_number_of_people(Event event)
{
	int position = this->find_event(event.get_title());
	Event new_event = Event(this->events.get_element(position).get_title(), this->events.get_element(position).get_description(), this->events.get_element(position).get_the_date_time(), this->events.get_element(position).get_the_number_of_people()-1, this->events.get_element(position).get_the_link());
	events.delete_item(position);
	events.add_item(new_event);
}

DynamicVector<Event> Repository::get_events()
{
	return events;
}
