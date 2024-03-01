#include "CsvUserList.h"
#include <Windows.h>
#include <shellapi.h>
#include "RepositoryExceptions.h"

void CsvUserList::save_to_file()
{
	std::ofstream the_file(file_name);

	if (!the_file.is_open())
		throw FileException("File not opened");

	for (auto one_event : this->events)
		the_file << one_event.get_title() << "," << one_event.get_description() << "," << one_event.get_the_date_time() << "," << one_event.get_the_number_of_people() << "," << one_event.get_the_link() << "\n";
	the_file.close();
}

void CsvUserList::open_file()
{
	system("notepad.exe userlist.csv");
}
