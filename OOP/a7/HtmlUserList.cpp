#include "HtmlUserList.h"
#include <Windows.h>
#include <shellapi.h>
#include "RepositoryExceptions.h"

void HtmlUserList::save_to_file()
{
	std::ofstream the_file(this->file_name);

	if (!the_file.is_open())
		throw FileException("File not opened");

	the_file << "<!DOCTYPE html>" << "\n";
	the_file << "<html>" << "\n";

	the_file << "<head>" << "\n";
	the_file << "<title>Events</title>" << "\n";
	the_file << "</head>" << "\n";


	the_file << "<body>" << "\n";

	the_file << "<table border=\"1\">" << "\n";

	the_file << "<tr>" << "\n";
	the_file << "<td>Title</td>" << "\n";
	the_file << "<td>Description</td>" << "\n";
	the_file << "<td>Date</td>" << "\n";
	the_file << "<td>Number of people</td>" << "\n";
	the_file << "<td>Link</td>" << "\n";
	the_file << "</tr>" << "\n";

	for (auto i : this->events)
	{
		the_file << "<tr>" << "\n";

		the_file << "<td>" << i.get_title() << "</td>" << "\n";
		the_file << "<td>" << i.get_description() << "</td>" << "\n";
		the_file << "<td>" << i.get_the_date_time() << "</td>" << "\n";
		the_file << "<td>" << i.get_the_number_of_people() << "</td>" << "\n";
		the_file << "<td><a href =" << i.get_the_link() << ">Link</a></td>";

		the_file << "</tr>" << "\n";
	}

	the_file << "</table>" << "\n";

	the_file << "</body>" << "\n";

	the_file << "</html>" << "\n";
	the_file.close();
}

void HtmlUserList::open_file()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", "file:///C:/Users/Anita/source/repos/a7-913-Gorog-Anita-1/a7/a7/userlist.html", NULL, SW_SHOWMAXIMIZED);
}
