/********************************************************************************
** Form generated from reading UI file 'AdminWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINWIDGET_H
#define UI_ADMINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
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

class Ui_AdminWidgetClass
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *event_date_input;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *event_link_input;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *event_description_input;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *event_title;
    QLineEdit *event_title_input;
    QListWidget *list_widget;
    QPushButton *add_event_button;
    QPushButton *delete_event_button;
    QPushButton *update_event_button;
    QLabel *label_3;
    QLineEdit *event_number_of_people_input;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AdminWidgetClass)
    {
        if (AdminWidgetClass->objectName().isEmpty())
            AdminWidgetClass->setObjectName("AdminWidgetClass");
        AdminWidgetClass->resize(696, 364);
        centralWidget = new QWidget(AdminWidgetClass);
        centralWidget->setObjectName("centralWidget");
        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(10, 110, 311, 71));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_3);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        event_date_input = new QLineEdit(horizontalLayoutWidget_3);
        event_date_input->setObjectName("event_date_input");

        horizontalLayout_3->addWidget(event_date_input);

        horizontalLayoutWidget_5 = new QWidget(centralWidget);
        horizontalLayoutWidget_5->setObjectName("horizontalLayoutWidget_5");
        horizontalLayoutWidget_5->setGeometry(QRect(10, 200, 311, 81));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget_5);
        label_4->setObjectName("label_4");

        horizontalLayout_5->addWidget(label_4);

        event_link_input = new QLineEdit(horizontalLayoutWidget_5);
        event_link_input->setObjectName("event_link_input");

        horizontalLayout_5->addWidget(event_link_input);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 50, 311, 91));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        event_description_input = new QLineEdit(horizontalLayoutWidget_2);
        event_description_input->setObjectName("event_description_input");

        horizontalLayout_2->addWidget(event_description_input);

        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 0, 311, 81));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        event_title = new QLabel(horizontalLayoutWidget);
        event_title->setObjectName("event_title");

        horizontalLayout->addWidget(event_title);

        event_title_input = new QLineEdit(horizontalLayoutWidget);
        event_title_input->setObjectName("event_title_input");

        horizontalLayout->addWidget(event_title_input);

        list_widget = new QListWidget(centralWidget);
        list_widget->setObjectName("list_widget");
        list_widget->setGeometry(QRect(320, 1, 361, 291));
        add_event_button = new QPushButton(centralWidget);
        add_event_button->setObjectName("add_event_button");
        add_event_button->setGeometry(QRect(20, 280, 75, 24));
        delete_event_button = new QPushButton(centralWidget);
        delete_event_button->setObjectName("delete_event_button");
        delete_event_button->setGeometry(QRect(120, 280, 75, 24));
        update_event_button = new QPushButton(centralWidget);
        update_event_button->setObjectName("update_event_button");
        update_event_button->setGeometry(QRect(220, 280, 75, 24));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 180, 101, 16));
        event_number_of_people_input = new QLineEdit(centralWidget);
        event_number_of_people_input->setObjectName("event_number_of_people_input");
        event_number_of_people_input->setGeometry(QRect(120, 180, 201, 21));
        AdminWidgetClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AdminWidgetClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 696, 22));
        AdminWidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AdminWidgetClass);
        mainToolBar->setObjectName("mainToolBar");
        AdminWidgetClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AdminWidgetClass);
        statusBar->setObjectName("statusBar");
        AdminWidgetClass->setStatusBar(statusBar);

        retranslateUi(AdminWidgetClass);

        QMetaObject::connectSlotsByName(AdminWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *AdminWidgetClass)
    {
        AdminWidgetClass->setWindowTitle(QCoreApplication::translate("AdminWidgetClass", "AdminWidget", nullptr));
        label_2->setText(QCoreApplication::translate("AdminWidgetClass", "Date of event", nullptr));
        label_4->setText(QCoreApplication::translate("AdminWidgetClass", "Link", nullptr));
        label->setText(QCoreApplication::translate("AdminWidgetClass", "Description of event", nullptr));
        event_title->setText(QCoreApplication::translate("AdminWidgetClass", "Title of event", nullptr));
        add_event_button->setText(QCoreApplication::translate("AdminWidgetClass", "Add", nullptr));
        delete_event_button->setText(QCoreApplication::translate("AdminWidgetClass", "Delete", nullptr));
        update_event_button->setText(QCoreApplication::translate("AdminWidgetClass", "Update", nullptr));
        label_3->setText(QCoreApplication::translate("AdminWidgetClass", "Number of people", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminWidgetClass: public Ui_AdminWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINWIDGET_H
