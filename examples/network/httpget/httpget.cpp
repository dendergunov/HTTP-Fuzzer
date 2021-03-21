#include <QCoreApplication>
#include "httpmanager.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HttpManager manager;

    return a.exec();
}

