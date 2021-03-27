#ifndef REPLYHEADERMODEL_HPP
#define REPLYHEADERMODEL_HPP

#include <QtCore/QAbstractTableModel>
#include <QList>
#include <QNetworkReply>

namespace Model{

class ReplyHeaderModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ReplyHeaderModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setReplyHeaders(QList<QNetworkReply::RawHeaderPair> &&rawHeaderList);
    void setReplyHeaders(const QList<QNetworkReply::RawHeaderPair> &rawHeaderList);
private:
    static constexpr int columns_ = 2;
    QList<QNetworkReply::RawHeaderPair> storage_;
};

}

#endif // REPLYHEADERMODEL_HPP
