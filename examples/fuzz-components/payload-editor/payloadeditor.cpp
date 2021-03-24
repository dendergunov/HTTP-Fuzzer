#include "payloadeditorwidget.hpp"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    PayloadEditorWidget pew;
    pew.show();
    return a.exec();
}
