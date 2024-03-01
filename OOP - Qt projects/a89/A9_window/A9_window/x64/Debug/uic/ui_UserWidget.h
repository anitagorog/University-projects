/********************************************************************************
** Form generated from reading UI file 'UserWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERWIDGET_H
#define UI_USERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserWidgetClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLineEdit *filter_events_input;
    QPushButton *filter_events_button;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *event_title_input;
    QLineEdit *event_description_input;
    QLineEdit *event_date_input;
    QPushButton *add_event_button;
    QPushButton *next_event_button;
    QPushButton *export_user_list_button;
    QLabel *label_5;
    QLineEdit *delete_event_input;
    QPushButton *delete_event_button;
    QListWidget *user_list_widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UserWidgetClass)
    {
        if (UserWidgetClass->objectName().isEmpty())
            UserWidgetClass->setObjectName("UserWidgetClass");
        UserWidgetClass->resize(722, 400);
        centralWidget = new QWidget(UserWidgetClass);
        centralWidget->setObjectName("centralWidget");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 71, 16));
        filter_events_input = new QLineEdit(centralWidget);
        filter_events_input->setObjectName("filter_events_input");
        filter_events_input->setGeometry(QRect(90, 20, 231, 21));
        filter_events_button = new QPushButton(centralWidget);
        filter_events_button->setObjectName("filter_events_button");
        filter_events_button->setGeometry(QRect(20, 50, 301, 24));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 90, 81, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 120, 111, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 150, 81, 16));
        event_title_input = new QLineEdit(centralWidget);
        event_title_input->setObjectName("event_title_input");
        event_title_input->setGeometry(QRect(100, 90, 221, 21));
        event_description_input = new QLineEdit(centralWidget);
        event_description_input->setObjectName("event_description_input");
        event_description_input->setGeometry(QRect(140, 120, 181, 21));
        event_date_input = new QLineEdit(centralWidget);
        event_date_input->setObjectName("event_date_input");
        event_date_input->setGeometry(QRect(100, 150, 221, 21));
        add_event_button = new QPushButton(centralWidget);
        add_event_button->setObjectName("add_event_button");
        add_event_button->setGeometry(QRect(20, 190, 101, 24));
        next_event_button = new QPushButton(centralWidget);
        next_event_button->setObjectName("next_event_button");
        next_event_button->setGeometry(QRect(130, 190, 91, 24));
        export_user_list_button = new QPushButton(centralWidget);
        export_user_list_button->setObjectName("export_user_list_button");
        export_user_list_button->setGeometry(QRect(230, 190, 91, 24));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 240, 261, 16));
        delete_event_input = new QLineEdit(centralWidget);
        delete_event_input->setObjectName("delete_event_input");
        delete_event_input->setGeometry(QRect(20, 270, 301, 21));
        delete_event_button = new QPushButton(centralWidget);
        delete_event_button->setObjectName("delete_event_button");
        delete_event_button->setGeometry(QRect(20, 300, 301, 24));
        user_list_widget = new QListWidget(centralWidget);
        user_list_widget->setObjectName("user_list_widget");
        user_list_widget->setGeometry(QRect(350, 10, 361, 331));
        UserWidgetClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(UserWidgetClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 722, 22));
        UserWidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(UserWidgetClass);
        mainToolBar->setObjectName("mainToolBar");
        UserWidgetClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(UserWidgetClass);
        statusBar->setObjectName("statusBar");
        UserWidgetClass->setStatusBar(statusBar);

        retranslateUi(UserWidgetClass);

        QMetaObject::connectSlotsByName(UserWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *UserWidgetClass)
    {
        UserWidgetClass->setWindowTitle(QCoreApplication::translate("UserWidgetClass", "UserWidget", nullptr));
        label->setText(QCoreApplication::translate("UserWidgetClass", "Filter events", nullptr));
        filter_events_button->setText(QCoreApplication::translate("UserWidgetClass", "Filter", nullptr));
        label_2->setText(QCoreApplication::translate("UserWidgetClass", "Title of event", nullptr));
        label_3->setText(QCoreApplication::translate("UserWidgetClass", "Description of event", nullptr));
        label_4->setText(QCoreApplication::translate("UserWidgetClass", "Date of event", nullptr));
        add_event_button->setText(QCoreApplication::translate("UserWidgetClass", "Add event to list", nullptr));
        next_event_button->setText(QCoreApplication::translate("UserWidgetClass", "Show next", nullptr));
        export_user_list_button->setText(QCoreApplication::translate("UserWidgetClass", "Export my list", nullptr));
        label_5->setText(QCoreApplication::translate("UserWidgetClass", "Enter the title of event you would like to delete", nullptr));
        delete_event_button->setText(QCoreApplication::translate("UserWidgetClass", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserWidgetClass: public Ui_UserWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERWIDGET_H
