#include "fuzzmanager.hpp"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>

FuzzManager::FuzzManager(QObject *parent) : QObject(parent),
    timer_(new QTimer{this}),
    qnam_(new QNetworkAccessManager{this})
{
    connect(timer_, &QTimer::timeout, this, &FuzzManager::sendRequest);
    qDebug() << "I was born!";
}

void FuzzManager::fuzz(int count, int delay){
    requestCount_ = count;
    requestSent_ = 0;
    replyCount_ = 0;
    for(auto& x: rr_)
        if(x.reply != nullptr)
            x.reply->deleteLater();
    rr_.clear();
    emit fuzzRestarted();
    emit progressChanged(0);
    timer_->start(delay);
}

void FuzzManager::sendRequest()
{
    if(cancelled_){
        emit done(tr("Fuzzing cacelled"));
        timer_->stop();
        return;
    }
    if(requestSent_ == requestCount_){
        timer_->stop();
        return;
    }
    QUrl qurl(QStringLiteral("http://google.com"));
    QNetworkRequest request(qurl);
    rr_.append({qnam_->get(request), {}, {}});
    qDebug() << "Request" << requestSent_ << "sent!";
    connect(rr_.last().reply, &QNetworkReply::finished, [i=requestSent_, this](){
        qDebug() << "Finished" << i+1 << "request";
        ++replyCount_;
        int newProgressPercent = static_cast<int>(100*replyCount_/requestCount_);
        if(progressPercent_ != newProgressPercent){
            progressPercent_ = newProgressPercent;
            emit progressChanged(progressPercent_);
        }
        qDebug() << "total replyCount_" << replyCount_;
        RequestResult reqres = rr_.at(i);
        reqres.replyBody = QString::fromUtf8(reqres.reply->readAll());
        rr_.replace(i, reqres);

        QVariant toSend;
        toSend.setValue(rr_.at(i));
        emit replyProcessed(toSend);
        if(replyCount_ == requestCount_)
            emit done(tr("Fuzzing done"));
    });
    ++requestSent_;

}

void FuzzManager::setCancelled(bool value)
{
    cancelled_ = value;
}
