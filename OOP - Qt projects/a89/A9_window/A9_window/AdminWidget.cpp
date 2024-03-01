#include "AdminWidget.h"

AdminWidget::AdminWidget(Service* service, QWidget *parent)
	: QMainWindow(parent), service(*service)
{
	ui.setupUi(this);
	this->populate_the_list_widget();
	this->make_connections();
}

AdminWidget::~AdminWidget()
{}

void AdminWidget::clear_line_edits()
{
	this->ui.event_title_input->clear();
	this->ui.event_description_input->clear();
	this->ui.event_date_input->clear();
	this->ui.event_number_of_people_input->clear();
	this->ui.event_link_input->clear();
}

void AdminWidget::make_connections()
{
	QObject::connect(this->ui.add_event_button, SIGNAL(clicked()), this, SLOT(add_event_in_gui()));
	QObject::connect(this->ui.delete_event_button, SIGNAL(clicked()), this, SLOT(delete_event_from_gui()));
	QObject::connect(this->ui.update_event_button, SIGNAL(clicked()), this, SLOT(update_event_in_gui()));
}

void AdminWidget::populate_the_list_widget()
{
	for (auto event : this->service.get_all_events())
	{
		ui.list_widget->addItem(QString::fromStdString(event.to_string()));
	}
}

void AdminWidget::delete_event_from_gui()
{
	this->ui.list_widget->clear();

	std::string title = this->ui.event_title_input->text().toStdString();
	//std::string description = this->event_description_input->text().toStdString();
	//std::string date = this->event_date_input->text().toStdString();
	//std::string number_of_people = this->event_number_of_people_input->text().toStdString();
	//std::string link = this->event_link_input->text().toStdString();

	try
	{
		this->service.delete_event_from_repository(title);
	}
	catch (RepositoryException& the_exception)
	{
	}

	for (auto event : this->service.get_all_events())
	{
		ui.list_widget->addItem(QString::fromStdString(event.to_string()));
	}

	this->clear_line_edits();

	try
	{
		this->service.save_to_file();
	}
	catch (FileException& the_exception)
	{
	}
}

void AdminWidget::update_event_in_gui()
{
	this->ui.list_widget->clear();

	std::string title = this->ui.event_title_input->text().toStdString();
	std::string description = this->ui.event_description_input->text().toStdString();
	std::string date = this->ui.event_date_input->text().toStdString();
	std::string number_of_people = this->ui.event_number_of_people_input->text().toStdString();
	std::string link = this->ui.event_link_input->text().toStdString();

	try
	{
		this->service.update_event_from_repository(title, description, stoi(date), stoi(number_of_people), link);
	}
	catch (RepositoryException& the_exception)
	{
	}

	for (auto event : this->service.get_all_events())
	{
		ui.list_widget->addItem(QString::fromStdString(event.to_string()));
	}

	this->clear_line_edits();

	try
	{
		this->service.save_to_file();
	}
	catch (FileException& the_exception)
	{
	}
}

void AdminWidget::add_event_in_gui()
{
	this->ui.list_widget->clear();

	std::string title = this->ui.event_title_input->text().toStdString();
	std::string description = this->ui.event_description_input->text().toStdString();
	std::string date = this->ui.event_date_input->text().toStdString();
	std::string number_of_people = this->ui.event_number_of_people_input->text().toStdString();
	std::string link = this->ui.event_link_input->text().toStdString();

	try
	{
		this->service.add_event_to_repository(title, description, stoi(date), stoi(number_of_people), link);
	}
	catch (EventException& the_exceptions)
	{
	}
	catch (RepositoryException& the_exception)
	{
	}

	for (auto event : this->service.get_all_events())
	{
		ui.list_widget->addItem(QString::fromStdString(event.to_string()));
	}

	this->clear_line_edits();

	try
	{
		this->service.save_to_file();
	}
	catch (FileException& the_exception)
	{
	}
}
