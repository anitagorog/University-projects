#pragma once
#include "Event.h"
#include <exception>
#include <vector>

class Validator
{
public:
	Validator();

	void validate_event(Event event);
};

class EventException
{
private:
	std::vector<std::string> validation_errors;

public:
	EventException(std::vector<std::string> validation_errors);
	std::vector<std::string> get_validation_errors();
};
