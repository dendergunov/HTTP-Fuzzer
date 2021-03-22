#include "liststringwidget.hpp"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListStringWidget lsw;
    lsw.show();

    return a.exec();
}
