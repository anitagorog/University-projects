#pragma once
#include "Event.h"
#include <vector>


class RepositoryInterface
{
public:
	RepositoryInterface();
	~RepositoryInterface();

	virtual std::vector<Event> get_events() = 0;
	//virtual Event get_current_event() = 0;
	//virtual int get_length() = 0;

	virtual void add_event(const Event event) = 0;
	virtual void delete_event(const Event event) = 0;
	virtual void update_event(const Event event) = 0;
	virtual void increase_number_of_people(Event event) = 0;
	virtual void decrease_number_of_people(Event event) = 0;
	virtual void save_to_file() = 0;
};

