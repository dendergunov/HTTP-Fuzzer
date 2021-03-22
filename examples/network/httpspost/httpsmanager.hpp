#ifndef HTTPSMANAGER_HPP
#define HTTPSMANAGER_HPP

#include <QtCore/QObject>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QList>
#include <QSslError>

class HttpsManager : public QObject
{
    Q_OBJECT
private:
    void doSession();
    QNetworkAccessManager qnam_;
public:
    explicit HttpsManager(QObject *parent = nullptr);

private slots:

};

#endif // HTTPSMANAGER_HPP
