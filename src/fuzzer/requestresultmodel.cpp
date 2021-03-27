#include "requestresultmodel.hpp"

namespace Model{
RequestResultModel::RequestResultModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant RequestResultModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        switch(section){
        case 0:
            return tr("Status code");
        case 1:
            return tr("URL");
        case 2:
            return tr("Request body");
        case 3:
            return tr("Reply body");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

int RequestResultModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return storage_.size();
}

int RequestResultModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return columns_;
}

QVariant RequestResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() >= storage_.size() || index.row() < 0)
        return QVariant();

    const RequestResult& rr = storage_.at(index.row());

    switch(role){
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch(index.column()){
        case 0:
            return rr.reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        case 1:
            return rr.reply->url();
        case 2:
            return rr.requestBody;
        case 3:
            return rr.replyBody;
        }
    }

    return QVariant();
}

void RequestResultModel::appendRequestResult(const RequestResult& rr)
{
    int row = storage_.size();
    QModelIndex index = this->index(row, 0);
    beginInsertRows(index, row, row);
    storage_.append(rr);
    endInsertRows();

}

void RequestResultModel::clearData()
{
    beginResetModel();
    storage_.clear();
    endResetModel();
}
}
