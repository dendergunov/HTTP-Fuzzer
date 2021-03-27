#include "repeater/guirepeater.hpp"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QList<PayloadRow>>();
    qRegisterMetaType<RequestResult>();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Repeater::GuiRepeater w;
    w.show();
    return a.exec();
}
