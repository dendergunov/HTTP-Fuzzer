#ifndef REQUESTRESULT_HPP
#define REQUESTRESULT_HPP

#include <QString>
#include <QNetworkReply>
#include <QMetaType>

struct RequestResult
{
    QNetworkReply *reply;
    QString requestBody;
    QString replyBody;
};

Q_DECLARE_METATYPE(RequestResult)

#endif // REQUESTRESULT_HPP
