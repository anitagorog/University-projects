#pragma once
#include "Event.h"
#include "DynamicVector.h"

class Repository
{
private:
	DynamicVector<Event> events;

public:
	Repository() {}

	// Check if already exists, otherwise insert in the container
	void add_event(const Event event);
	// Check if exists, if so deletes from the container, otherwise gives a message
	void delete_event(const Event event);
	// Check if exists, if so updates in the container, otherwise gives a message
	void update_event(const Event event);

	// Finds the position of an event by its array, if does not exist return -1
	int find_event(const std::string title);

	// Increases the number of people of the input event
	void increase_number_of_people(Event event);
	// Decreases the number of people of the input event
	void decrease_number_of_people(Event event);

	// Returns all the events in the list
	DynamicVector<Event> get_events();

};

