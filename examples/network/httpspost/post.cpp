#include <QCoreApplication>
#include "httpsmanager.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HttpsManager manager;

    return a.exec();
}
