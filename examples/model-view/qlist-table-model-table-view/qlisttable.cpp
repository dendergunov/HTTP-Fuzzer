#include "qlisttablewidget.hpp"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QListTableWidget widget;
    widget.show();
    return a.exec();
}
