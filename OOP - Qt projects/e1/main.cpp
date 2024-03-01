#include "Practic.h"
#include <QtWidgets/QApplication>
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Service s;
    s.read_f();
    s.read_p();
    for (auto d : s.get_docs())
    {
        Practic* w = new Practic{d.get_spec(), s};
        w->setWindowTitle(QString::fromStdString(d.get_name()));
        w->show();
    }
    //s.save();
    return a.exec();
}
