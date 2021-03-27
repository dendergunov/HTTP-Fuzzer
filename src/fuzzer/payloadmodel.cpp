#include "payloadmodel.hpp"

namespace Model{
PayloadModel::PayloadModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant PayloadModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        switch(section){
        case 0:
            return tr("Insert Position");
        case 1:
            return tr("# of Payloads");
        case 2:
            return tr("Payloads");
        }
    } else if(orientation == Qt::Vertical)
        return ++section;

    return QVariant();
}

int PayloadModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return storage_.size();
}

int PayloadModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return columns_;
}

QVariant PayloadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row() >= storage_.size() || index.row() < 0)
        return QVariant();

    PayloadRow payloadRow = storage_.at(index.row());

    switch(role){
    case Qt::EditRole:
        switch(index.column()){
        case 0:
        {
            QVariant store;
            store.setValue(payloadRow.startLength);
            return store;
        }
        break;
        case 1:
            return payloadRow.subStringList.size();
            break;
        case 2:
            return payloadRow.subStringList;
            break;
        }

    case Qt::DisplayRole:
        switch(index.column()){
        case 0:
            return QString(QStringLiteral("[") + QString::number(payloadRow.startLength.first)
                           + QStringLiteral(";") + QString::number(payloadRow.startLength.first
                                                                   + payloadRow.startLength.second - 1)
                           + QStringLiteral("]"));
            break;
        case 1:
            return payloadRow.subStringList.size();
            break;
        case 2:
            return payloadRow.subStringList.join(QStringLiteral("; "));
            break;
        }
        break;
    }

    return QVariant();
}

bool PayloadModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (data(index, role) != value) {
        int row = index.row();
        int column = index.column();

        PayloadRow payloadRow(storage_.at(row));

        switch (column) {
        case 0:
            //ToDo: add check to substring indexes overlapping
            if(!value.canConvert<substringCoordinates>())
                return false;
            else
                payloadRow.startLength = value.value<substringCoordinates>();
            break;
        case 1:
            return false;
        case 2:

            if(!value.canConvert<QStringList>())
                return false;
            else
                payloadRow.subStringList = value.toStringList();
        }

        storage_.replace(index.row(), payloadRow);
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PayloadModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (index.column()==1)
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

bool PayloadModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for(int i=0; i<count; ++i){
        storage_.insert(row, {{-1,0},{}});
    }
    endInsertRows();

    return true;
}

bool PayloadModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for(int i=0; i<count; ++i)
        storage_.removeAt(row);
    endRemoveRows();

    return true;
}

bool PayloadModel::isSubStringOverlap(const substringCoordinates& coords, int row)
{
    int insertStart = coords.first,
        insertEnd = insertStart + coords.second - 1;

    for(int i=0; i<storage_.size(); ++i){
        substringCoordinates stored(storage_.at(i).startLength);
        if(i!=row && ((insertStart <= (stored.first + stored.second - 1)
                          && insertEnd >= (stored.first + stored.second - 1))
                         || (stored.first <=  insertEnd
                             && (stored.first + stored.second - 1) >= insertEnd)))
            return true;
    }
    return false;
}

const QList<PayloadRow>& PayloadModel::payloadRows()
{
    return storage_;
}
}
