#include "guirepeater.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    GuiRepeater repeater;
    repeater.show();
    return a.exec();
}
