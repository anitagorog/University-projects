/********************************************************************************
** Form generated from reading UI file 'A9_window.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A9_WINDOW_H
#define UI_A9_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_A9_windowClass
{
public:
    QWidget *centralWidget;
    QPushButton *admin_button;
    QPushButton *user_button;
    QRadioButton *csv_button;
    QRadioButton *html_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *A9_windowClass)
    {
        if (A9_windowClass->objectName().isEmpty())
            A9_windowClass->setObjectName("A9_windowClass");
        A9_windowClass->resize(474, 366);
        centralWidget = new QWidget(A9_windowClass);
        centralWidget->setObjectName("centralWidget");
        admin_button = new QPushButton(centralWidget);
        admin_button->setObjectName("admin_button");
        admin_button->setGeometry(QRect(150, 60, 141, 41));
        user_button = new QPushButton(centralWidget);
        user_button->setObjectName("user_button");
        user_button->setGeometry(QRect(150, 120, 141, 41));
        csv_button = new QRadioButton(centralWidget);
        csv_button->setObjectName("csv_button");
        csv_button->setGeometry(QRect(110, 200, 101, 21));
        html_button = new QRadioButton(centralWidget);
        html_button->setObjectName("html_button");
        html_button->setGeometry(QRect(110, 240, 89, 20));
        A9_windowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(A9_windowClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 474, 22));
        A9_windowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(A9_windowClass);
        mainToolBar->setObjectName("mainToolBar");
        A9_windowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(A9_windowClass);
        statusBar->setObjectName("statusBar");
        A9_windowClass->setStatusBar(statusBar);

        retranslateUi(A9_windowClass);

        QMetaObject::connectSlotsByName(A9_windowClass);
    } // setupUi

    void retranslateUi(QMainWindow *A9_windowClass)
    {
        A9_windowClass->setWindowTitle(QCoreApplication::translate("A9_windowClass", "A9_window", nullptr));
        admin_button->setText(QCoreApplication::translate("A9_windowClass", "Admin", nullptr));
        user_button->setText(QCoreApplication::translate("A9_windowClass", "User", nullptr));
        csv_button->setText(QCoreApplication::translate("A9_windowClass", "CSV", nullptr));
        html_button->setText(QCoreApplication::translate("A9_windowClass", "HTML", nullptr));
    } // retranslateUi

};

namespace Ui {
    class A9_windowClass: public Ui_A9_windowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A9_WINDOW_H
