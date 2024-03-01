#include "UserWidget.h"

UserWidget::UserWidget(Service* service, QWidget *parent)
	: QMainWindow(parent), service(*service)
{
	ui.setupUi(this);
	user_list = UserList();

	this->make_connections_between_functions_and_buttons();
}

UserWidget::~UserWidget()
{}

void UserWidget::make_connections_between_functions_and_buttons()
{
	QObject::connect(this->ui.add_event_button, SIGNAL(clicked()), this, SLOT(add_event_to_user_gui()));
	QObject::connect(this->ui.next_event_button, SIGNAL(clicked()), this, SLOT(show_next_event_in_user_gui()));
	QObject::connect(this->ui.filter_events_button, SIGNAL(clicked()), this, SLOT(filter_events_in_user_gui()));
	QObject::connect(this->ui.export_user_list_button, SIGNAL(clicked()), this, SLOT(save_events_from_user_gui()));
	QObject::connect(this->ui.delete_event_button, SIGNAL(clicked()), this, SLOT(delete_event_in_user_gui()));
}

void UserWidget::add_event_to_user_gui()
{
	this->service.add_event_to_user_list(this->user_list.get_current_event());
	this->user_list.delete_event(this->user_list.get_current_event());
	ui.user_list_widget->clear();
	for (auto event : this->service.get_user_list())
	{
		ui.user_list_widget->addItem(QString::fromStdString(event.to_string()));
	}
	this->show_next_event_in_user_gui();
}

void UserWidget::show_next_event_in_user_gui()
{
	if (!this->user_list.is_empty())
	{
		this->user_list.go_to_next();
		std::string title, description;
		int date;
		title = this->user_list.get_current_event().get_title();
		description = this->user_list.get_current_event().get_description();
		date = this->user_list.get_current_event().get_the_date_time();
		this->ui.event_title_input->setText(QString::fromStdString(title));
		this->ui.event_description_input->setText(QString::fromStdString(description));
		this->ui.event_date_input->setText(QString::fromStdString(std::to_string(date)));
		this->user_list.open_site();
	}
	else
	{
		this->ui.event_title_input->clear();
		this->ui.event_description_input->clear();
		this->ui.event_date_input->clear();
	}
}

void UserWidget::filter_events_in_user_gui()
{
	std::string month = this->ui.filter_events_input->text().toStdString();

	for (char const& ch : month)
	{
		if (std::isdigit(ch) == 0) {
			return;
		}
	}

	user_list = this->service.get_events_for_given_month(month);
	if (!this->user_list.is_empty())
	{
		std::string title, description;
		int date;
		title = this->user_list.get_current_event().get_title();
		description = this->user_list.get_current_event().get_description();
		date = this->user_list.get_current_event().get_the_date_time();
		this->ui.event_title_input->setText(QString::fromStdString(title));
		this->ui.event_description_input->setText(QString::fromStdString(description));
		this->ui.event_date_input->setText(QString::fromStdString(std::to_string(date)));
		this->user_list.open_site();
	}
	else
	{
		this->ui.event_title_input->clear();
		this->ui.event_description_input->clear();
		this->ui.event_date_input->clear();
	}
}

void UserWidget::delete_event_in_user_gui()
{
	std::string title_of_event_to_delete = this->ui.delete_event_input->text().toStdString();
	try
	{
		this->service.delete_event_from_user_list(title_of_event_to_delete);
	}
	catch (InexistentException& the_exception)
	{
	}

	ui.user_list_widget->clear();
	for (auto event : this->service.get_user_list())
	{
		ui.user_list_widget->addItem(QString::fromStdString(event.to_string()));
	}
	this->ui.delete_event_input->clear();
}

void UserWidget::save_events_from_user_gui()
{
	try
	{
		this->service.save_to_file();
	}
	catch (FileException& the_exception)
	{
	}
}
