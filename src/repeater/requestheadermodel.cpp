#include "requestheadermodel.hpp"

#include <QString>

namespace Model{

RequestHeaderModel::RequestHeaderModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant RequestHeaderModel::headerData(int section, Qt::Orientation orientation, int role) const
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
    } else if(orientation == Qt::Vertical){
        return ++section;
    }

    return QVariant();
}

int RequestHeaderModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return storage_.size();
}

int RequestHeaderModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return columns_;
}

QVariant RequestHeaderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= storage_.size() || index.row() < 0)
        return QVariant();

    const QPair<QByteArray, QByteArray>& pair = storage_.at(index.row());

    switch(role){
    case Qt::DisplayRole:
        if(index.column()==0)
            return QString::fromUtf8(pair.first);
        else if(index.column()==1)
            return QString::fromUtf8(pair.second);
        break;
    case Qt::EditRole:
        if(index.column()==0)
            return pair.first;
        else if(index.column()==1)
            return pair.second;
    }

    return QVariant();
}

bool RequestHeaderModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        int row = index.row();
        int column = index.column();

        QPair<QByteArray, QByteArray> pair(storage_.at(row));

        if(column==0)
            pair.first= value.toByteArray();
        else if(column==1)
            pair.second= value.toByteArray();

        storage_.replace(row, pair);

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags RequestHeaderModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled; // FIXME: Implement me!
}

bool RequestHeaderModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for(int i=0; i<count; ++i){
        storage_.insert(row, QPair<QByteArray, QByteArray>("<key>", "<value>"));
    }
    endInsertRows();

    return true;
}


bool RequestHeaderModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for(int i=0; i<count; ++i)
        storage_.removeAt(row);
    endRemoveRows();

    return true;
}

const QList<QPair<QByteArray, QByteArray>>& RequestHeaderModel::requestHeaders() const
{
    return storage_;
}

void RequestHeaderModel::setRequestHeaders(const QList<QPair<QByteArray, QByteArray> > &headers)
{
    beginResetModel();
    storage_ = headers;
    endResetModel();
}
}
