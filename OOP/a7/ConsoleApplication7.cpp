
#include <iostream>
#include "Ui.h"
#include "Test.h"
#include <crtdbg.h>
#include "CsvUserList.h"
#include "HtmlUserList.h"
#include "RepositoryExceptions.h"

void make_initial_elements(Repository& repository)
{
	Event event = Event("Event1", "description1", 22032023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
	event = Event("Event2", "description2", 22062023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
	event = Event("Event3", "description3", 22032023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
	event = Event("Event4", "description4", 22032023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
	event = Event("Event5", "description5", 22032023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
	event = Event("Event6", "description6", 22032023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
	event = Event("Event7", "description7", 22032023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
	event = Event("Event8", "description8", 22032023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
	event = Event("Event9", "description9", 22032023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
	event = Event("Event10", "description10", 22072023, 2, "https://www.facebook.com/events/1014477312857367/?ref=newsfeed");
	repository.add_event(event);
}

int main()
{
	{
		Test::tests();
		std::string type_of_file;
		while (1)
		{
			std::cout << "\nChoose file type (csv or html):\n";
			std::cout << "Or: exit\n";
			std::getline(std::cin, type_of_file);
			if (type_of_file == "exit")
			{
				break;
			}
			if (type_of_file == "csv" || type_of_file == "html")
			{
				try {
					FileRepository* admin_repository = new FileRepository{ "events.txt" };
					//make_initial_elements(*admin_repository);
					FileUserList* user_repository = nullptr;
					if (type_of_file == "csv")
						user_repository = new CsvUserList{ "userlist.csv" };
					else
						user_repository = new HtmlUserList{ "userlist.html" };
					Service service{ *admin_repository, user_repository };
					Ui ui{ service };
					ui.run_program();
					delete admin_repository;
					delete user_repository;
				}
				catch (FileException&)
				{
					std::cout << "Could not be opened";
					return 1;
				}
			}
		}
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
