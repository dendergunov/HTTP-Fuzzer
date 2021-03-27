#ifndef PAYLOADLISTDELEGATE_HPP
#define PAYLOADLISTDELEGATE_HPP

#include <QtWidgets/QStyledItemDelegate>
#include <qstyleditemdelegate.h>

namespace Delegate{

class PayloadListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem& option,
                          const QModelIndex &index) const override;
};
}
#endif // PAYLOADLISTDELEGATE_HPP
