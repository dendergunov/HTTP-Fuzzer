#ifndef PAYLOADMODEL_HPP
#define PAYLOADMODEL_HPP

#include "customtypes.hpp"

#include <QtCore/QAbstractTableModel>

#include<QPair>
#include<QStringList>

struct PayloadRow{
    substringCoordinates startLength;
    QStringList subStringList;
};

class PayloadModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PayloadModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool isSubStringOverlap(const substringCoordinates& coords, int row = -1);

private:
    constexpr static int columns_ = 3;
    QList<PayloadRow> storage_;
};

#endif // PAYLOADMODEL_HPP
