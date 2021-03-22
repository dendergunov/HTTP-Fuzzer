#include "httpmanager.hpp"
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QString>

HttpManager::HttpManager(QObject *parent) : QObject(parent)
{
    QTextStream(stdout) << "Simple Qt Network example" << endl;
    connect(&qnam_, &QNetworkAccessManager::finished, [=](QNetworkReply *reply){
        QTextStream out(stdout);
        out << "Got reply from " << reply->url().toString() << endl;
        if(reply->error()==QNetworkReply::NoError){
            QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            out << "Status code:" << statusCode.toInt() << endl;
            out << "Reply body:" << endl << reply->readAll() << endl;
        }
    });
    sendRequest();
}

void HttpManager::sendRequest()
{
    QTextStream out(stdout);
    QNetworkRequest request(QUrl::fromEncoded("http://neverssl.com"));
    out << "Create HTTP GET request to:" << request.url().toString() << endl;
    qnam_.get(request);
}
