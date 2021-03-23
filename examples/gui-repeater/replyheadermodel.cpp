#include "replyheadermodel.hpp"

#include <QNetworkReply>
#include <QList>

ReplyHeaderModel::ReplyHeaderModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant ReplyHeaderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        switch(section){
        case 0:
            return tr("Key");
        case 1:
            return tr("Value");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

int ReplyHeaderModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return storage_.size();
}

int ReplyHeaderModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return columns_;
}

QVariant ReplyHeaderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() >= storage_.size() || index.row() < 0)
        return QVariant();

    QNetworkReply::RawHeaderPair pair = storage_.at(index.row());

    switch(role){
    case Qt::DisplayRole:
        if(index.column()==0)
            return pair.first;
        else if(index.column() == 1)
            return pair.second;
    }

    return QVariant();
}

void ReplyHeaderModel::setReplyHeaders(QList<QNetworkReply::RawHeaderPair> &&rawHeaderList)
{
    beginResetModel();
    storage_ = rawHeaderList;
    endResetModel();
}

void ReplyHeaderModel::setReplyHeaders(const QList<QNetworkReply::RawHeaderPair> &rawHeaderList)
{
    beginResetModel();
    storage_ = rawHeaderList;
    endResetModel();
}
