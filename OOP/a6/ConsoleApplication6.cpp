
#include <iostream>
#include "Ui.h"
#include "Test.h"
#include <crtdbg.h>

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
		Repository repository{};
		make_initial_elements(repository);
		Service service{ repository };
		Ui ui{ service };
		ui.run_program();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}

// TESTS !!!!!!