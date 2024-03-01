#pragma once

#include <QtWidgets/QWidget>
#include "ui_Practic.h"
#include "Service.h"
#include "qmessagebox.h"

class Practic : public QWidget, public Observer
{
    Q_OBJECT

public:
    Practic(std::string spec, Service& ser, QWidget *parent = nullptr);
    ~Practic();

    void update() { this->populate(); }
    void populate();
    void conn();
    void ad_pat();
    void filter();
    void upd();

private:
    Ui::PracticClass ui;
    std::string spec;
    Service& ser;
};
