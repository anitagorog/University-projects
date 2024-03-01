#include "Test.h"
#include <assert.h>
#include "Repository.h"
#include "Service.h"
#include "UserList.h"

void Test::tests()
{
	test_event(); 
	tests_repository();
	test_user_list();
}

void Test::test_event()
{
	std::cout << "Test Event" << '\n';
	Event test_event = Event("aa", "bb", 2, 2, "hh");
	assert(test_event.get_title() == "aa");
	assert(test_event.get_description() == "bb");
	assert(test_event.get_the_date_time() == 2);
	assert(test_event.get_the_number_of_people() == 2);
	assert(test_event.get_the_link() == "hh");
}

void Test::tests_repository()
{
	std::cout << '\n' << "Test Repository" << '\n';
	Repository repository = Repository();
	Event event1 = Event("aa", "bb", 3, 3, "dd");
	repository.add_event(event1);
	int position = repository.find_event("ff");
	assert(position == -1);
	position = repository.find_event("aa");
	assert(position != -1);
	repository.delete_event(event1);
	std::vector<Event> events = repository.get_events();
	assert(events.size() == 0);
}

void Test::test_user_list()
{
	std::cout << '\n' << "Test User list" << '\n';
	UserList test_list;
	assert(test_list.get_size() == 0);
	test_list.open_site();
	assert(test_list.is_empty() == true);
	Event event = Event("aa", "bb", 2, 2, "hh");
	test_list.add(event);
	std::vector<Event> another_test_list = test_list.get_events();
	assert(test_list.get_current_event().get_title() == event.get_title());
	test_list.delete_event(event);
	assert(test_list.get_size() == 0);
	assert(test_list.is_empty() == true);
	event = Event("aa", "bb", 2, 2, "hh");
	test_list.add(event);
	assert(test_list.get_current_event().get_title() == event.get_title());
	event = Event("cc", "bb", 2, 2, "hh");
	test_list.add(event);
	test_list.go_to_next();
	assert(test_list.get_current_event().get_title() == event.get_title());
	event = Event("kk", "bb", 2, 2, "hh");
	test_list.add(event);
	test_list.go_to_next();
	test_list.go_to_next();
}

/*void Test::test_service()
{
	std::cout << '\n' << "Test Service" << '\n';
	Repository repository{};
	UserList test_list{};
	Service service{ repository };
	Event event = Event("cc", "bb", 2, 2, "hh");
	service.add_event_to_repository("cc", "bb", 2, 2, "hh");
	assert(repository.find_event("cc") != 1);
	service.add_event_to_user_list(event);
	service.update_event_from_repository("cc", "bbb", 2, 2, "hh");
	service.get_all_events();
	service.delete_event_from_repository("cc");
	assert(repository.find_event("cc") == -1);
	event = Event("aa", "bb", 20032023, 2, "hh");
	service.add_event_to_repository("aa", "bb", 20032023, 2, "hh");
	assert(service.get_events_for_given_month("03").get_size() == 1);
	assert(service.get_events_for_given_month("").get_size() == 1);
	service.get_user_list();
	service.delete_event_from_user_list("aa");
	assert(service.get_user_list().is_empty() == false);
}*/
