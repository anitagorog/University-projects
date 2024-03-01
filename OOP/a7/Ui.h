#pragma once
#include "Service.h"

class Ui
{
private:
	Service service;

public:
	Ui(const Service service) : service(service) {}

	void run_program();
	void run_admin_mode();
	void run_user_mode();

private:
	static void print_menu();
	static void print_menu_admin();
	static void print_menu_user();

	void add_event_to_array();
	void delete_event_from_array();
	void update_event_in_array();
	void list_all_events();

	void make_list_for_user();
	void print_menu_for_making_user_list();
	void print_list_made_by_user(std::vector<Event> list);
	void delete_event_from_user_list();
};

