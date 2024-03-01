#pragma once

#include <QMainWindow>
#include "ui_UserWidget.h"
#include "Service.h"
#include "UserList.h"
#include "RepositoryExceptions.h"

class UserWidget : public QMainWindow
{
	Q_OBJECT

public:
	UserWidget(Service* service, QWidget *parent = nullptr);
	~UserWidget();

private:
	Ui::UserWidgetClass ui;

private:
	Service service;
	UserList user_list;

	void make_connections_between_functions_and_buttons();

private slots:
	void add_event_to_user_gui();
	void show_next_event_in_user_gui();
	void filter_events_in_user_gui();
	void delete_event_in_user_gui();
	void save_events_from_user_gui();
};
