#pragma once
#include <qwidget.h>
#include <QtWidgets/qtablewidget.h>
#include "Service.h"
#include "RepositoryExceptions.h"
#include <QtWidgets>
#include <qboxlayout.h>

namespace DEFAULT
{
    const int SPACING = 30;
    const int COLUMN_COUNT = 5;
    const int TITLE_COLUMN = 0;
    const int TITLE_WIDTH = 200;
    const int DESCRIPTION_COLUMN = 1;
    const int DATE_COLUMN = 2;
    const int NUMBER_OF_PEOPLE_COLUMN = 3;
    const int LINK_COLUMN = 4;
}

class AdminWidget :
    public QWidget
{
    Q_OBJECT

private:
    Service service;

private slots:
    void add_event_in_gui();
    void delete_event_from_gui();
    void update_event_in_gui();

private:
    QPushButton* add_event_button;
    QPushButton* delete_event_button;
    QPushButton* update_event_button;
    QListWidget* list_widget;
    QLineEdit* event_title_input;
    QLineEdit* event_description_input;
    QLineEdit* event_date_input;
    QLineEdit* event_number_of_people_input;
    QLineEdit* event_link_input;
    void clear_line_edits();

public:
    AdminWidget(Service* service, QWidget* parent = nullptr);
    QListWidget* create_list_widget();
    QHBoxLayout* create_buttons();
    QHBoxLayout* create_event_title_layout();
    QHBoxLayout* create_event_description_layout();
    QHBoxLayout* create_event_date_layout();
    QHBoxLayout* create_event_number_of_people_layout();
    QHBoxLayout* create_event_link_layout();
};

