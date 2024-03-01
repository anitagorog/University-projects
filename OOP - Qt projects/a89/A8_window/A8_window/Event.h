#pragma once
#include <string>
#include <iostream>

class Event
{
private:
	std::string title;
	std::string description;
	int date_time;
	int number_of_people;
	std::string link; 

public:
	Event();
	Event(const std::string the_title, const std::string the_description, const int the_date_time, const int the_number_of_people, const std::string the_link);

	std::string get_title() const;
	std::string get_description() const;
	int get_the_date_time() const;
	int get_the_number_of_people() const;
	std::string get_the_link() const;
	std::string to_string();

	void open_the_site();

	bool operator==(const Event& event) const;
};
