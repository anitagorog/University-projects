#include "UserWidget.h"

using namespace DEFAULT;

UserWidget::UserWidget(Service* service, QWidget* parent) : service(*service)
{
	user_list = UserList();

	QVBoxLayout* event_filter = create_filter_event_layout();
	QVBoxLayout* delete_event_layout = create_delete_event_layout();
	QVBoxLayout* user_list_information = create_user_list_information(event_filter, delete_event_layout);
	QHBoxLayout* user_list_information_with_the_list_of_their_events = new QHBoxLayout;

	user_list_information_with_the_list_of_their_events->addLayout(user_list_information);
	user_list_widget = new QListWidget;
	user_list_information_with_the_list_of_their_events->addWidget(user_list_widget);

	this->setLayout(user_list_information_with_the_list_of_their_events);

	this->make_connections_between_functions_and_buttons();
}

QVBoxLayout* UserWidget::create_filter_event_layout()
{
	QHBoxLayout* filter_events_group = new QHBoxLayout;
	QVBoxLayout* filter_events_group_with_button = new QVBoxLayout;
	QLabel* filter_events = new QLabel("Filter events", this);
	filter_events_input = new QLineEdit(this);
	filter_events_button = new QPushButton("Filter", this);
	filter_events_group->addWidget(filter_events);
	filter_events_group->addWidget(filter_events_input);
	filter_events_group_with_button->addLayout(filter_events_group);
	filter_events_group_with_button->addWidget(filter_events_button);
	return filter_events_group_with_button;
}

QVBoxLayout* UserWidget::create_delete_event_layout()
{
	QVBoxLayout* delete_event_layout = new QVBoxLayout;
	QLabel* delete_event = new QLabel("Enter the title of event you would like to delete", this);
	delete_event_input = new QLineEdit(this);
	delete_event_button = new QPushButton("Delete", this);
	delete_event_layout->addWidget(delete_event);
	delete_event_layout->addWidget(delete_event_input);
	delete_event_layout->addWidget(delete_event_button);
	return delete_event_layout;
}

QHBoxLayout* UserWidget::create_event_title_layout()
{
	QLabel* event_title = new QLabel("Title of event", this);
	event_title_input = new QLineEdit(this);
	QHBoxLayout* event_title_group = new QHBoxLayout;
	event_title_group->addWidget(event_title);
	event_title_group->addWidget(event_title_input);
	return event_title_group;
}

QHBoxLayout* UserWidget::create_event_description_layout()
{
	QLabel* event_description = new QLabel("Description of event", this);
	event_description_input = new QLineEdit(this);
	QHBoxLayout* event_description_group = new QHBoxLayout;
	event_description_group->addWidget(event_description);
	event_description_group->addWidget(event_description_input);
	return event_description_group;
}

QHBoxLayout* UserWidget::create_event_date_layout()
{
	QLabel* event_date = new QLabel("Date of event", this);
	event_date_input = new QLineEdit(this);
	QHBoxLayout* event_date_group = new QHBoxLayout;
	event_date_group->addWidget(event_date);
	event_date_group->addWidget(event_date_input);
	return event_date_group;
}

QHBoxLayout* UserWidget::create_buttons_layout()
{
	QHBoxLayout* buttons = new QHBoxLayout;
	add_event_button = new QPushButton("Add event to list", this);
	next_event_button = new QPushButton("Show next", this);   
	export_user_list_button = new QPushButton("Export my list", this);
	buttons->addWidget(add_event_button);
	buttons->addWidget(next_event_button);
	buttons->addWidget(export_user_list_button);
	return buttons;
}

QVBoxLayout* UserWidget::create_user_list_information(QVBoxLayout* filtered_events_group, QVBoxLayout* delete_event_from_layout)
{
	QVBoxLayout* event_information = new QVBoxLayout;
	QHBoxLayout* buttons = create_buttons_layout();
	QHBoxLayout* event_title = create_event_title_layout();
	QHBoxLayout* event_description = create_event_description_layout();
	QHBoxLayout* event_date = create_event_date_layout();

	event_information->setSpacing(SPACING_USER);
	event_information->addLayout(filtered_events_group);
	event_information->addLayout(event_title);
	event_information->addLayout(event_description);
	event_information->addLayout(event_date);
	event_information->addLayout(buttons);
	event_information->addLayout(delete_event_from_layout);

	return event_information;
}

void UserWidget::make_connections_between_functions_and_buttons()
{
	QObject::connect(this->add_event_button, SIGNAL(clicked()), this, SLOT(add_event_to_user_gui()));
	QObject::connect(this->next_event_button, SIGNAL(clicked()), this, SLOT(show_next_event_in_user_gui()));
	QObject::connect(this->filter_events_button, SIGNAL(clicked()), this, SLOT(filter_events_in_user_gui()));
	QObject::connect(this->export_user_list_button, SIGNAL(clicked()), this, SLOT(save_events_from_user_gui()));
	QObject::connect(this->delete_event_button, SIGNAL(clicked()), this, SLOT(delete_event_in_user_gui()));
}

void UserWidget::add_event_to_user_gui()
{
	this->service.add_event_to_user_list(this->user_list.get_current_event());
	this->user_list.delete_event(this->user_list.get_current_event());
	user_list_widget->clear();
	for (auto event : this->service.get_user_list())
	{
		user_list_widget->addItem(QString::fromStdString(event.to_string()));
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
		this->event_title_input->setText(QString::fromStdString(title));
		this->event_description_input->setText(QString::fromStdString(description));
		this->event_date_input->setText(QString::fromStdString(std::to_string(date)));
		this->user_list.open_site();
	}
	else
	{
		this->event_title_input->clear();
		this->event_description_input->clear();
		this->event_date_input->clear();
	}
}

void UserWidget::filter_events_in_user_gui()
{
	std::string month = this->filter_events_input->text().toStdString();

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
		this->event_title_input->setText(QString::fromStdString(title));
		this->event_description_input->setText(QString::fromStdString(description));
		this->event_date_input->setText(QString::fromStdString(std::to_string(date)));
		this->user_list.open_site();
	}
	else
	{
		this->event_title_input->clear();
		this->event_description_input->clear();
		this->event_date_input->clear();
	}
}

void UserWidget::delete_event_in_user_gui()
{
	std::string title_of_event_to_delete = this->delete_event_input->text().toStdString();
	try
	{ 
	this->service.delete_event_from_user_list(title_of_event_to_delete);
	}
	catch (InexistentException& the_exception)
	{
	}

	user_list_widget->clear();
	for (auto event : this->service.get_user_list())
	{
		user_list_widget->addItem(QString::fromStdString(event.to_string()));
	}
	this->delete_event_input->clear();
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
