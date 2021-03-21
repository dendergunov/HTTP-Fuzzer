#include "httpmanager.hpp"
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QString>

HttpManager::HttpManager(QObject *parent) : QObject(parent)
{
    QTextStream(stdout) << "Simple Qt Network example" << endl;
    sendRequest();
}

void HttpManager::sendRequest()
{
    QTextStream out(stdout);
    QNetworkRequest request(QUrl::fromEncoded("http://neverssl.com"));
    out << "Create HTTP request to:" << request.url().toString() << endl;
    QNetworkReply *reply = qnam_.get(request);
    connect(reply, &QNetworkReply::finished, [=](){
        QTextStream out(stdout);
        out << "Got reply!" << endl;
        if(reply->error())
            out << reply->error();
        else
            out << reply->readAll();
    });
}
