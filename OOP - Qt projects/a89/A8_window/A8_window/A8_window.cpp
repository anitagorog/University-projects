#include "A8_window.h"

A8_window::A8_window(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("Event managing application");
    
    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(this->admin_button);
    main_layout->addWidget(this->user_button);
    main_layout->addWidget(this->csv_button);
    main_layout->addWidget(this->html_button);
    this->ui.centralWidget->setLayout(main_layout);

    this->form_interface();
}

A8_window::~A8_window()
{}

void A8_window::form_interface()
{
    QObject::connect(this->admin_button, SIGNAL(clicked()), this, SLOT(admin_form()));
    QObject::connect(this->user_button, SIGNAL(clicked()), this, SLOT(user_form()));
}

void A8_window::admin_form()
{
    FileRepository admin_repository = FileRepository{ "events.txt" };
    FileUserList* user_repository = new CsvUserList("userlist.csv");
    if (this->csv_button->isChecked() == true)
        user_repository = new CsvUserList("userlist.csv");
    else if (this->html_button->isChecked() == true)
        user_repository = new HtmlUserList("userlist.html");
    this->service = new Service(admin_repository, user_repository);
    AdminWidget* widget = new AdminWidget(this->service);
    widget->show();
}

void A8_window::user_form()
{
    FileRepository admin_repository = FileRepository{ "events.txt" };
    FileUserList* user_repository = new CsvUserList("userlist.csv");
    if (this->csv_button->isChecked() == true)
        user_repository = new CsvUserList("userlist.csv");
    else if (this->html_button->isChecked() == true)
        user_repository = new HtmlUserList("userlist.html");
    this->service = new Service(admin_repository, user_repository);
    UserWidget* widget = new UserWidget(this->service);
    widget->show();
}
