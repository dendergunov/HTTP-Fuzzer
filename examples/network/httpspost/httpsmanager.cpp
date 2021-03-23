#include "httpsmanager.hpp"
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QList>
#include <QSslError>
#include <QAuthenticator>
#include <QString>
#include <QVariant>

HttpsManager::HttpsManager(QObject *parent) : QObject(parent)
{
    QTextStream qout(stdout);
    qout << "HTTPS Post request example" << endl;

    connect(&qnam_, &QNetworkAccessManager::finished, [=](QNetworkReply *reply){
        QTextStream qout(stdout);
        qout << "Got reply from " << reply->url().toString() << endl;
        if(reply->error()==QNetworkReply::NoError){
            QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            qout << "Status code:" << statusCode.toInt() << endl;
            qout << "Reply body:" << endl << reply->readAll() << endl;
        }
        reply->deleteLater();
    });

    doSession();
}

void HttpsManager::doSession()
{
    QTextStream qout(stdout);
    QUrl url(QUrl(QStringLiteral("https://webhook.site/e9fc18fe-e381-49c1-bb11-573c606aadee")));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("text/plain"));
    qout << "Test 1" << endl;
    qout << "Create HTTPS request to:" << request.url().toString() << endl;
    qnam_.post(request, "Simple POST body");

    url = QUrl(QStringLiteral("https://ptsv2.com/t/wwutz-1616347262/post"));
    request.setUrl(url);
    qout << "Test 2" << endl;
    qout << "Create HTTPS request to:" << request.url().toString() << endl;
    qout << url.host() << endl;
    qnam_.post(request, "No diference what to send!");
}

