#include "A8_window.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    A8_window w;
    w.show();
    return a.exec();
}
