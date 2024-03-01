#include "AdminWidget.h"

using namespace DEFAULT;

void AdminWidget::delete_event_from_gui()
{
	this->list_widget->clear();

	std::string title = this->event_title_input->text().toStdString();
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
		list_widget->addItem(QString::fromStdString(event.to_string()));
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
	this->list_widget->clear();

	std::string title = this->event_title_input->text().toStdString();
	std::string description = this->event_description_input->text().toStdString();
	std::string date = this->event_date_input->text().toStdString();
	std::string number_of_people = this->event_number_of_people_input->text().toStdString();
	std::string link = this->event_link_input->text().toStdString();

	try
	{
	this->service.update_event_from_repository(title, description, stoi(date), stoi(number_of_people), link);
	}	
	catch (RepositoryException& the_exception)
	{
	}

	for (auto event : this->service.get_all_events())
	{
		list_widget->addItem(QString::fromStdString(event.to_string()));
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
	this->list_widget->clear();

	std::string title = this->event_title_input->text().toStdString();
	std::string description = this->event_description_input->text().toStdString();
	std::string date = this->event_date_input->text().toStdString();
	std::string number_of_people = this->event_number_of_people_input->text().toStdString();
	std::string link = this->event_link_input->text().toStdString();

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
		list_widget->addItem(QString::fromStdString(event.to_string()));
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

void AdminWidget::clear_line_edits()
{
	this->event_title_input->clear();
	this->event_description_input->clear();
	this->event_date_input->clear();
	this->event_number_of_people_input->clear();
	this->event_link_input->clear();
}

AdminWidget::AdminWidget(Service* service, QWidget* parent) : QWidget(parent), service(*service)
{
	QHBoxLayout* admin_layout = new QHBoxLayout;
	QVBoxLayout* event_information_layout = new QVBoxLayout;
	
	QHBoxLayout* buttons = create_buttons();

	QHBoxLayout* event_title = this->create_event_title_layout();
	QHBoxLayout* event_description = this->create_event_description_layout();
	QHBoxLayout* event_date = this->create_event_date_layout();
	QHBoxLayout* event_number_of_people = this->create_event_number_of_people_layout();
	QHBoxLayout* event_link = this->create_event_link_layout();

	event_information_layout->setSpacing(SPACING);
	event_information_layout->addLayout(event_title);
	event_information_layout->addLayout(event_description);
	event_information_layout->addLayout(event_date);
	event_information_layout->addLayout(event_number_of_people);
	event_information_layout->addLayout(event_link);
	event_information_layout->addLayout(buttons);

	admin_layout->addLayout(event_information_layout);
	list_widget = this->create_list_widget();
	admin_layout->addWidget(list_widget);
	this->setLayout(admin_layout);

	QObject::connect(this->add_event_button, SIGNAL(clicked()), this, SLOT(add_event_in_gui()));
	QObject::connect(this->delete_event_button, SIGNAL(clicked()), this, SLOT(delete_event_from_gui()));
	QObject::connect(this->update_event_button, SIGNAL(clicked()), this, SLOT(update_event_in_gui()));
}

QListWidget* AdminWidget::create_list_widget()
{
	list_widget = new QListWidget();
	for (auto event : this->service.get_all_events())
	{
		list_widget->addItem(QString::fromStdString(event.to_string()));
	}
	return list_widget;
}

QHBoxLayout* AdminWidget::create_buttons()
{
	QHBoxLayout* buttons = new QHBoxLayout();
	add_event_button = new QPushButton("Add event", this);
	delete_event_button = new QPushButton("Delete event", this);
	update_event_button = new QPushButton("Update event", this);

	buttons->addWidget(add_event_button);
	buttons->addWidget(delete_event_button);
	buttons->addWidget(update_event_button);

	return buttons;
}

QHBoxLayout* AdminWidget::create_event_title_layout()
{
	QLabel* event_title = new QLabel("Title of event", this);
	event_title_input = new QLineEdit(this);
	QHBoxLayout* event_title_group = new QHBoxLayout();
	event_title_group->addWidget(event_title);
	event_title_group->addWidget(event_title_input);

	return event_title_group;
}

QHBoxLayout* AdminWidget::create_event_description_layout()
{
	QLabel* event_description = new QLabel("Description of event", this);
	event_description_input = new QLineEdit(this);
	QHBoxLayout* event_description_group = new QHBoxLayout();
	event_description_group->addWidget(event_description);
	event_description_group->addWidget(event_description_input);

	return event_description_group;
}

QHBoxLayout* AdminWidget::create_event_date_layout()
{
	QLabel* event_date = new QLabel("Date of event", this);
	event_date_input = new QLineEdit(this);
	QHBoxLayout* event_date_group = new QHBoxLayout();
	event_date_group->addWidget(event_date);
	event_date_group->addWidget(event_date_input);

	return event_date_group;
}

QHBoxLayout* AdminWidget::create_event_number_of_people_layout()
{
	QLabel* event_number_of_people = new QLabel("Number_of_people of event", this);
	event_number_of_people_input = new QLineEdit(this);
	QHBoxLayout* event_number_of_people_group = new QHBoxLayout();
	event_number_of_people_group->addWidget(event_number_of_people);
	event_number_of_people_group->addWidget(event_number_of_people_input);

	return event_number_of_people_group;
}

QHBoxLayout* AdminWidget::create_event_link_layout()
{
	QLabel* event_link = new QLabel("Link of event", this);
	event_link_input = new QLineEdit(this);
	QHBoxLayout* event_link_group = new QHBoxLayout();
	event_link_group->addWidget(event_link);
	event_link_group->addWidget(event_link_input);

	return event_link_group;
}
