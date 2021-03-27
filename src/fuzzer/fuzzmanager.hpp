#ifndef FUZZMANAGER_HPP
#define FUZZMANAGER_HPP

#include "customtypes.hpp"

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QList>
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QAtomicInt>
#include <QtNetwork/QNetworkRequest>
#include <QPair>
#include <QByteArray>
#include <QString>

namespace Fuzz{

class FuzzManager : public QObject
{
    Q_OBJECT

public:
    explicit FuzzManager(QObject *parent = nullptr);

public:
    void setCancelled(bool value);
public slots:
    void fuzzStart(const QString& url, const QString& body, const QList<QPair<QByteArray, QByteArray>>& requestHeaders,
                   const QList<PayloadRow>& urlPayload, const QList<PayloadRow>& bodyPayload,
                   const QString& method, int delay);

signals:
    void progressChanged(int percent);
    void done(const QString& result);
    void replyProcessed(const RequestResult& rr);
    void fuzzRestarted();

private slots:
    void sendRequest();

private:
    QAtomicInt cancelled_ = 0;
    int requestCount_ = 0;
    int requestSent_ = 0;
    int replyCount_ = 0;

    int progressPercent_ = 0;

    int totalUrlPayloads_ = 1;
    int totalBodyPayloads_ = 1;

    QTimer *timer_;
    QNetworkAccessManager *qnam_;

    QNetworkRequest request_;
    QString url_, body_, method_;
    QList<RequestResult> rr_;
    QList<PayloadRow> urlPayload_,
        bodyPayload_;
    QList<QPair<QByteArray, QByteArray>> requestHeaders_;
};
}
#endif // FUZZMANAGER_HPP
