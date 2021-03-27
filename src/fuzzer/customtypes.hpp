#ifndef CUSTOMTYPES_HPP
#define CUSTOMTYPES_HPP

#include <QMetaType>
#include <QPair>
#include <QString>
#include <QNetworkReply>

struct RequestResult
{
    QNetworkReply *reply;
    QString requestBody;
    QString replyBody;
};
Q_DECLARE_METATYPE(RequestResult)

typedef QPair<int, int> substringCoordinates;
Q_DECLARE_METATYPE(substringCoordinates)

struct PayloadRow{
    substringCoordinates startLength;
    QStringList subStringList;
};
Q_DECLARE_METATYPE(PayloadRow)

#endif // CUSTOMTYPES_HPP
