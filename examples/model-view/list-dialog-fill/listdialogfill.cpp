#include "payloadwidget.hpp"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PayloadWidget pw;
    pw.show();
    return a.exec();
}
