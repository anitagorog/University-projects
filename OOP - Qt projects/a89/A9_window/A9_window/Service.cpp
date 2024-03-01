#include "Service.h"

Service::Service()
{
	this->repository = FileRepository();
	this->user_list = nullptr;
}

void Service::save_to_file()
{
	this->repository.save_to_file(); 
	this->user_list->save_to_file();
}

void Service::open_the_file()
{
	this->user_list->open_file();
}

void Service::add_event_to_repository(const std::string the_new_title, const std::string the_new_description, const int the_new_date_time, const int the_new_number_of_people, const std::string the_new_link)
{
	Event new_event = Event(the_new_title, the_new_description, the_new_date_time, the_new_number_of_people, the_new_link);
	this->validator.validate_event(new_event);
	this->repository.add_event(new_event);
}

void Service::delete_event_from_repository(const std::string title)
{
	Event event_to_delete_by_its_title = Event(title, "", 0, 0, "");
	this->repository.delete_event(event_to_delete_by_its_title);
}

void Service::update_event_from_repository(const std::string the_title, const std::string the_new_description, const int the_new_date_time, const int the_new_number_of_people, const std::string the_new_link)
{
	Event event_to_update_with_given_title = Event(the_title, the_new_description, the_new_date_time, the_new_number_of_people, the_new_link);
	this->repository.update_event(event_to_update_with_given_title);
}

std::vector<Event> Service::get_all_events()
{
	return this->repository.get_events();
}

UserList Service::get_events_for_given_month(std::string month)
{
	UserList list_for_storing_events_with_given_month;
	Event event;
	if (month == "")
	{
		for (auto event : this->repository.get_events())
		{
			list_for_storing_events_with_given_month.add(event);
		}
	}
	else {
		for (auto event : this->repository.get_events())
		{
			if (event.get_the_date_time() / 10000 % 100 == stoi(month))
				list_for_storing_events_with_given_month.add(event);
		}
	}
	return list_for_storing_events_with_given_month;
}

void Service::add_event_to_user_list(Event event)
{
	this->user_list->add(event);
	this->repository.increase_number_of_people(event);
	this->user_list->change_number_of_people_user_list(event);
}

void Service::delete_event_from_user_list(std::string title)
{
	Event event_to_delete_by_title = Event(title, "", 0, 0, "");
	this->user_list->delete_event(event_to_delete_by_title);
	this->repository.decrease_number_of_people(event_to_delete_by_title);
}

std::vector<Event> Service::get_user_list()
{
	return user_list->get_events();
}


