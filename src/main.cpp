#include "fuzzwidget.hpp"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FuzzWidget w;
    w.show();
    return a.exec();
}
