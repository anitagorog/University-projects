#include "FileRepository.h"
#include "RepositoryExceptions.h"

void FileRepository::load_from_file()
{
	std::ifstream the_file(this->file_name);

	if (!the_file.is_open())
		throw FileException("File not opened");
	if (the_file.is_open())
	{
		std::string one_line, argument;
		std::string title, description, link;
		int date_time = 0;
		int number_of_people = 0;
		while (std::getline(the_file, one_line))
		{
			//std::getline(the_file, one_line);
			/*if (the_file.eof() || one_line == "")
			{
				the_file.close();
				break;
			}*/
			//argument = splitString(one_line);
			std::stringstream string_stream(one_line);
			int count = 0;
			while (string_stream >> argument) {
				if (count == 0)
					title = argument;
				else if (count == 1)
					description = argument;
				else if (count == 2)
					date_time = stoi(argument);
				else if (count == 3)
					number_of_people = stoi(argument);
				else
					link = argument;
				count++;
			}
			this->add_event(Event{ title, description, date_time, number_of_people, link });
		}
		the_file.close();
	}
}

void FileRepository::save_to_file()
{
	std::ofstream the_file(this->file_name);

	if (!the_file.is_open())
		throw FileException("File not opened");

	std::vector<Event> all_events = this->get_events();
	for (int i = 0; i < all_events.size(); i++) {
		Event one_event = all_events[i];
		the_file << one_event.get_title() << " " << one_event.get_description() << " " << one_event.get_the_date_time() << " " << one_event.get_the_number_of_people() << " " << one_event.get_the_link() << "\n";
	}
	the_file.close();
}
