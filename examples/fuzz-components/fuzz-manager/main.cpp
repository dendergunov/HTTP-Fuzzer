#include "fuzzmanager.hpp"
#include "fuzzwidget.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FuzzWidget fw;
    fw.show();
    return a.exec();
}
