#include "Repository.h"

void Repository::add_event(const Event event)
{
	auto position = find(events.begin(), events.end(), event);
	if (position == events.end())
		this->events.push_back(event);
	else
		std::cout << "Duplicate event\n";
}

void Repository::delete_event(const Event event)
{
	int position = find_event(event.get_title());
	if (position == -1)
		std::cout << "Event not found\n";
	else
		this->events.erase(this->events.begin()+position);
}

void Repository::update_event(const Event event)
{
	int position = find_event(event.get_title());
	if (position == -1)
		std::cout << "Event not found\n";
	else
		this->events[position] = event;
}

int Repository::find_event(const std::string title_to_look_for)
{
	int i = 0;
	for (auto event : events)
	{
		if (event.get_title() == title_to_look_for)
			return i;
		i++;
	}
	return -1;
}

void Repository::increase_number_of_people(Event event)
{
	auto position = find(this->events.begin(), this->events.end(), event);
	Event new_event = Event(event.get_title(), event.get_description(), event.get_the_date_time(), event.get_the_number_of_people() + 1, event.get_the_link());
	events.erase(position);
	events.push_back(new_event);
}

void Repository::decrease_number_of_people(Event event)
{
	int position = find_event(event.get_title());
	Event new_event = Event(event.get_title(), event.get_description(), event.get_the_date_time(), event.get_the_number_of_people() - 1, event.get_the_link());
	events.erase(this->events.begin() + position);
	events.push_back(new_event);
}

std::vector<Event> Repository::get_events()
{
	return events;
}
