#ifndef REQUESTHEADERMODEL_HPP
#define REQUESTHEADERMODEL_HPP

#include <QtCore/QAbstractTableModel>
#include <QList>
#include <QPair>
#include <QByteArray>

class RequestHeaderModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RequestHeaderModel(QObject *parent = nullptr);

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

    const QList<QPair<QByteArray, QByteArray>>& requestHeaders() const;
private:
    static constexpr int columns_ = 2;
    QList<QPair<QByteArray, QByteArray>> storage_;
};

#endif // REQUESTHEADERMODEL_HPP
