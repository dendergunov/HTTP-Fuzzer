#ifndef HTTPMANAGER_HPP
#define HTTPMANAGER_HPP

#include <QtCore/QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextStream>

class HttpManager : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager qnam_;
    void sendRequest();

public:
    explicit HttpManager(QObject *parent = nullptr);
};

#endif // HTTPMANAGER_HPP
