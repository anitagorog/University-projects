#include "Validator.h"

Validator::Validator()
{
}

void Validator::validate_event(Event event)
{
    std::vector<std::string> validation_errors;
    if (!isupper(event.get_title()[0]))
        validation_errors.push_back("Title should start with capital letter. ");
    if (event.get_the_date_time() > 99999999 || event.get_the_date_time() < 10000000)
        validation_errors.push_back("Not valid date. ");
    if (event.get_the_number_of_people() < 1)
        validation_errors.push_back("Too few participants. ");
    int position_of_https_in_link = event.get_the_link().find("https");
    if (position_of_https_in_link != 0)
        validation_errors.push_back("The link is not valid. ");

    if (validation_errors.size() > 0)
        throw EventException(validation_errors);
}

EventException::EventException(std::vector<std::string> validation_errors)
{
    this->validation_errors = validation_errors;
}

std::vector<std::string> EventException::get_validation_errors()
{
    return this->validation_errors;
}
