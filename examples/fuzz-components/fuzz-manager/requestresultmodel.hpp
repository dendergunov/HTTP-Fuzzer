#ifndef REQUESTRESULTMODEL_HPP
#define REQUESTRESULTMODEL_HPP

#include "requestresult.hpp"

#include <QtCore/QAbstractTableModel>
#include <QList>

class RequestResultModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RequestResultModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void appendRequestResult(QVariant rr);
    void clearData();

private:
    static constexpr int columns_ = 4;
    QList<RequestResult> storage_;
};

#endif // REQUESTRESULTMODEL_HPP
