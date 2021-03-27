#include "fuzzmanager.hpp"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QPair>
#include <QByteArray>

#include <algorithm>

namespace Fuzz{
FuzzManager::FuzzManager(QObject *parent) : QObject(parent),
    timer_(new QTimer{this}),
    qnam_(new QNetworkAccessManager{this})
{
    connect(timer_, &QTimer::timeout, this, &FuzzManager::sendRequest);
}

void FuzzManager::fuzzStart(const QString& url, const QString& body, const QList<QPair<QByteArray, QByteArray>>& requestHeaders,
                            const QList<PayloadRow>& urlPayload, const QList<PayloadRow>& bodyPayload,
                            const QString& method, int delay){
    urlPayload_ = urlPayload;
    bodyPayload_ = bodyPayload;
    requestHeaders_ = requestHeaders;
    url_ = url;
    body_ = body;
    method_ = method;

    request_ = QNetworkRequest(QUrl(url_));
    for(auto& x: requestHeaders_)
        request_.setRawHeader(x.first, x.second);

    //to provde correct payload insertion into strings
    //we have to sort payload list in descending order,
    //iterate over list and insert payload as substring.
    //without sorting correct substitution is not guaranteed
    auto payloadComparator = [](const PayloadRow& a, const PayloadRow& b){
        return a.startLength.first > b.startLength.second;
    };

    std::sort(urlPayload_.begin(), urlPayload_.end(), payloadComparator);
    std::sort(bodyPayload_.begin(), bodyPayload_.end(), payloadComparator);

    totalUrlPayloads_ = 1;
    totalBodyPayloads_ = 1;

    for(auto& x: urlPayload_)
        totalUrlPayloads_ *= x.subStringList.size();

    for(auto& x: bodyPayload_)
        totalBodyPayloads_ *= x.subStringList.size();

    requestCount_ = totalUrlPayloads_ * totalBodyPayloads_;
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

    //to send request with every combination of payload
    //some algorithm is used to compute what substring to use
    //from each payloadrow based on request index

    int urlPayloadIndex = requestSent_ / totalBodyPayloads_,
        bodyPayloadIndex = requestSent_ % totalBodyPayloads_;

    int urlDimension = totalUrlPayloads_,
        bodyDimension = totalBodyPayloads_;

    int urlSlice = urlPayloadIndex,
        bodySlice = bodyPayloadIndex;

    //as payload lists are sorted we substitute a string at the end
    //keeping indexes of substring in begin correct

    QString url(url_), body(body_);

    for(auto& x: urlPayload_){
        int cardinality = x.subStringList.size();
        urlDimension /= cardinality;
        int listIndex = urlSlice / urlDimension;
        url.replace(x.startLength.first, x.startLength.second,
                    x.subStringList.at(listIndex));
        urlSlice %= urlDimension;
    }

    for(auto& x: bodyPayload_){
        int cardinality = x.subStringList.size();
        bodyDimension /= cardinality;
        int listIndex = bodySlice / bodyDimension;
        body.replace(x.startLength.first, x.startLength.second,
                     x.subStringList.at(listIndex));
        bodySlice %= bodyDimension;
    }

    QNetworkRequest request = request_;
    request.setUrl(QUrl(url));

    rr_.append({qnam_->sendCustomRequest(request, method_.toUtf8(), body.toUtf8()), body, {}});
    connect(rr_.last().reply, &QNetworkReply::finished, [i=requestSent_, this](){
        ++replyCount_;

        int newProgressPercent = static_cast<int>(100*replyCount_/requestCount_);
        if(progressPercent_ != newProgressPercent){
            progressPercent_ = newProgressPercent;
            emit progressChanged(progressPercent_);
        }

        RequestResult reqres = rr_.at(i);
        reqres.replyBody = QString::fromUtf8(reqres.reply->readAll());
        rr_.replace(i, reqres);
        emit replyProcessed(rr_.at(i));

        if(replyCount_ == requestCount_)
            emit done(tr("Fuzzing done"));
    });
    ++requestSent_;
}

void FuzzManager::setCancelled(bool value)
{
    cancelled_ = value;
}
}
