#pragma once
#include <qwidget.h>
#include <QtWidgets>
#include <qboxlayout.h>
#include "UserList.h"
#include "Service.h"
#include "RepositoryExceptions.h"

namespace DEFAULT
{
    const int SPACING_USER = 15;
}

class UserWidget :
    public QWidget
{
    Q_OBJECT

public:
    UserWidget(Service* service, QWidget* parent = nullptr);

    QVBoxLayout* create_filter_event_layout();
    QVBoxLayout* create_delete_event_layout();
    QHBoxLayout* create_event_title_layout();
    QHBoxLayout* create_event_description_layout();
    QHBoxLayout* create_event_date_layout();
    QHBoxLayout* create_buttons_layout();
    QVBoxLayout* create_user_list_information(QVBoxLayout* filtered_events_group, QVBoxLayout* delete_event_from_layout);

private:
    Service service;
    UserList user_list;

    QPushButton* add_event_button;
    QPushButton* next_event_button;
    QPushButton* export_user_list_button;
    QPushButton* delete_event_button;
    QPushButton* filter_events_button;
    QListWidget* user_list_widget;
    QLineEdit* filter_events_input;
    QLineEdit* event_title_input;
    QLineEdit* event_description_input;
    QLineEdit* event_date_input;
    QLineEdit* delete_event_input;
    QComboBox* user_list_file_type;

    void make_connections_between_functions_and_buttons();

private slots:
    void add_event_to_user_gui();
    void show_next_event_in_user_gui();
    void filter_events_in_user_gui();
    void delete_event_in_user_gui();
    void save_events_from_user_gui();
};

