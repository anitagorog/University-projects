#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_A8_window.h"
#include "Service.h"
#include "FileRepository.h"
#include "RepositoryExceptions.h"
#include "AdminWidget.h"
#include "UserWidget.h"
#include "CsvUserList.h"
#include "HtmlUserList.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class A8_window;
}
QT_END_NAMESPACE

class A8_window : public QMainWindow
{
    Q_OBJECT

private:
    Service* service;

    QRadioButton* csv_button = new QRadioButton("CSV");
    QRadioButton* html_button = new QRadioButton("HTML");
    QPushButton* admin_button = new QPushButton("Admin");
    QPushButton* user_button = new QPushButton("User");

public:
    A8_window(QWidget *parent = nullptr);
    ~A8_window();

    void form_interface();

private slots:
    void admin_form();
    void user_form();

private:
    Ui::A8_windowClass ui;
};
