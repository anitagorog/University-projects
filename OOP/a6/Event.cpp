#include "Event.h"
#include <Windows.h>
#include <shellapi.h>

Event::Event() : title(""), description(""), date_time(0), number_of_people(0), link("") {}

Event::Event(const std::string the_title, const std::string the_description, const int the_date_time, const int the_number_of_people, const std::string the_link)
{
	this->title = the_title;
	this->description = the_description;
	this->date_time = the_date_time;
	this->number_of_people = the_number_of_people;
	this->link = the_link;
}

std::string Event::get_title() const
{
	return title;
}

std::string Event::get_description() const
{
	return description;
}

int Event::get_the_date_time() const
{
	return date_time;
}

int Event::get_the_number_of_people() const
{
	return number_of_people;
}

std::string Event::get_the_link() const
{
	return link;
}

void Event::open_the_site()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->get_the_link().c_str(), NULL, SW_SHOWMAXIMIZED);
}

bool Event::operator==(const Event& event) const
{
	return this->title == event.title && this->number_of_people == event.number_of_people && this->description == event.description && this->date_time == event.date_time;
}
