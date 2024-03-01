#include "A9_window.h"

A9_window::A9_window(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->form_interface();
}

A9_window::~A9_window()
{}

void A9_window::form_interface()
{
    QObject::connect(this->ui.admin_button, SIGNAL(clicked()), this, SLOT(admin_form()));
    QObject::connect(this->ui.user_button, SIGNAL(clicked()), this, SLOT(user_form()));
}

void A9_window::user_form()
{
    FileRepository admin_repository = FileRepository{ "events.txt" };
    FileUserList* user_repository = new CsvUserList("userlist.csv");
    if (this->ui.csv_button->isChecked() == true)
        user_repository = new CsvUserList("userlist.csv");
    else if (this->ui.html_button->isChecked() == true)
        user_repository = new HtmlUserList("userlist.html");
    this->service = new Service(admin_repository, user_repository);
    UserWidget* widget = new UserWidget(this->service);
    widget->show();
}

void A9_window::admin_form()
{
    FileRepository admin_repository = FileRepository{ "events.txt" };
    FileUserList* user_repository = new CsvUserList("userlist.csv");
    if (this->ui.csv_button->isChecked() == true)
        user_repository = new CsvUserList("userlist.csv");
    else if (this->ui.html_button->isChecked() == true)
        user_repository = new HtmlUserList("userlist.html");
    this->service = new Service(admin_repository, user_repository);
    AdminWidget* widget = new AdminWidget(this->service);
    widget->show();
}
