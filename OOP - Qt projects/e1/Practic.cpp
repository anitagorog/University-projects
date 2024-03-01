#include "Practic.h"

Practic::Practic(std::string spec, Service& ser, QWidget *parent)
    : QWidget(parent), spec(spec), ser(ser)
{
    ui.setupUi(this);
    this->populate();
    this->ui.lineEdit->setText(QString::fromStdString(spec));
    this->conn();
    this->ser.add_obs(this);
    this->ser.notify();
    this->populate();
    
}

Practic::~Practic()
{}

void Practic::populate()
{
    this->ui.listWidget->clear();
    for (auto a : this->ser.get_pats())
    {
        if (a.get_diag() == "undiagnosed" || a.get_spec() == this->spec) {
            QListWidgetItem* it = new QListWidgetItem(QString::fromStdString(a.to_str()));
            if (a.get_doc() == this->windowTitle().toStdString())
                it->setBackground(Qt::green);
            this->ui.listWidget->addItem(it);
        }
    }
}

void Practic::conn()
{
    QObject::connect(this->ui.addbutton, &QPushButton::clicked, this, &Practic::ad_pat);
    QObject::connect(this->ui.checkBox, &QCheckBox::clicked, this, &Practic::filter);
    QObject::connect(this->ui.pushButtonupdate, &QPushButton::clicked, this, &Practic::upd);
}

void Practic::ad_pat()
{
    std::string na, diag = "undiagnosed", spec = this->spec, doc = this->windowTitle().toStdString(), dat;

    if (this->ui.linename->text().toStdString() == "" || this->ui.linedate->text().toStdString() == "" || this->ui.linedate->text().toInt() < 20231606) {
        QMessageBox::critical(this, "error", "invalid data");
        return;
    }

    na = this->ui.linename->text().toStdString();
    if (this->ui.linediag->text().toStdString() != "")
        diag = this->ui.linediag->text().toStdString();
    if (this->ui.linespec->text().toStdString() != "")
        spec = this->ui.linespec->text().toStdString();
    if (this->ui.linedoc->text().toStdString() != "")
        doc = this->ui.linedoc->text().toStdString();
    dat = this->ui.linedate->text().toStdString();
    this->ser.add_p(Patient(na, diag, spec, doc, stoi(dat)));
    this->ser.notify();
}

void Practic::filter()
{
    if (this->ui.checkBox->isChecked())
    {
        this->ui.listWidget->clear();
        for (auto a : this->ser.get_pats())
        {
            if ((a.get_diag() == "undiagnosed" || a.get_spec() == this->spec) && a.get_doc() == this->windowTitle().toStdString()) {
                QListWidgetItem* it = new QListWidgetItem(QString::fromStdString(a.to_str()));
                if (a.get_doc() == this->windowTitle().toStdString())
                    it->setBackground(Qt::green);
                this->ui.listWidget->addItem(it);
            }
        }
    }
    else
        this->populate();
}

void Practic::upd()
{
    std::string diag, spec;
    diag = this->ui.linediag->text().toStdString();
    spec = this->ui.linespec->text().toStdString();
    std::string name = this->ui.linename->text().toStdString();
    this->ser.update_pat(diag, spec, name, this->windowTitle().toStdString());
    this->ser.notify();
}
