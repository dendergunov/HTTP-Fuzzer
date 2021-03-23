#include "pairstringmodel.hpp"

PairStringModel::PairStringModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant PairStringModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int PairStringModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return storage_.size();
}

int PairStringModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return columns_;
}

QVariant PairStringModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() >= storage_.size() || index.row() < 0)
        return QVariant();

    QPair<QString, QString> pair = storage_.at(index.row());

    switch(role){
    case Qt::DisplayRole:

    case Qt::EditRole:
        if(index.column()==0)
            return pair.first;
        else if(index.column() == 1)
            return pair.second;
    }

    return QVariant();
}

bool PairStringModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        int row = index.row();
        int column = index.column();

        QPair<QString, QString> pair(storage_.at(row));

        if(column == 0)
            pair.first = value.toString();
        else if(column == 1)
            pair.second = value.toString();

        storage_.replace(row, pair);

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PairStringModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool PairStringModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for(int i=0; i<count; ++i){
        storage_.insert(row, QPair<QString, QString>(QStringLiteral("<key>"), QStringLiteral("<value>")));
    }
    endInsertRows();

    return true;
}

bool PairStringModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for(int i=0; i<count; ++i)
        storage_.removeAt(row);
    endRemoveRows();

    return false;
}

