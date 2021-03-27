#include "payloadlistdelegate.hpp"

#include <QtWidgets/QInputDialog>
#include <QStringList>

namespace Delegate{
QWidget* PayloadListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    QVariant data = index.data(Qt::EditRole);
    if(!data.canConvert<QStringList>())
        return QStyledItemDelegate::createEditor(parent, option, index);

    bool ok;
    QString payloadString = QInputDialog::getMultiLineText(parent, tr("Edit payload"), tr("Each payload is placed on new line"),
                                                             data.value<QStringList>().join(QStringLiteral("\n")), &ok);
    if(ok)
        const_cast<QAbstractItemModel*>(index.model())->setData(index, payloadString.split(QStringLiteral("\n")), Qt::EditRole);

    return nullptr;
}
}
