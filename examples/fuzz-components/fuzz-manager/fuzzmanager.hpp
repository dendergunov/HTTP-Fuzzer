#ifndef FUZZMANAGER_HPP
#define FUZZMANAGER_HPP

#include "requestresult.hpp"

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QList>
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QAtomicInt>

class FuzzManager : public QObject
{
    Q_OBJECT

public:
    explicit FuzzManager(QObject *parent = nullptr);

public:
    void setCancelled(bool value);
public slots:
    void fuzz(int count, int delay);

signals:
    void progressChanged(int percent);
    void done(const QString& result);
    void replyProcessed(QVariant rr);
    void fuzzRestarted();

private slots:
    void sendRequest();

private:
    QAtomicInt cancelled_ = 0;
    int requestCount_ = 0;
    int requestSent_ = 0;
    int replyCount_ = 0;
    int progressPercent_ = 0;
    QTimer *timer_;
    QNetworkAccessManager *qnam_;
    QList<RequestResult> rr_;
};

#endif // FUZZMANAGER_HPP
