#pragma once

#include <QMainWindow>
#include "ui_AdminWidget.h"
#include "Service.h"
#include "RepositoryExceptions.h"

class AdminWidget : public QMainWindow
{
	Q_OBJECT

public:
	AdminWidget(Service* service, QWidget *parent = nullptr);
	~AdminWidget();

private:
	Ui::AdminWidgetClass ui;

private:
	Service service;
	void clear_line_edits();
	void make_connections();
	void populate_the_list_widget();

private slots:
	void add_event_in_gui();
	void delete_event_from_gui();
	void update_event_in_gui();

};
