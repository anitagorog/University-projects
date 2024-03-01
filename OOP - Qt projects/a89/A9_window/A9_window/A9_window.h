#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_A9_window.h"
#include "Service.h"
#include "HtmlUserList.h"
#include "CsvUserList.h"
#include "AdminWidget.h"
#include "UserWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class A9_window;
}
QT_END_NAMESPACE

class A9_window : public QMainWindow
{
    Q_OBJECT

public:
    A9_window(QWidget *parent = nullptr);
    ~A9_window();

    void form_interface();

private:
    Service* service;

private slots:
    void admin_form();
    void user_form();

private:
    Ui::A9_windowClass ui;

};
