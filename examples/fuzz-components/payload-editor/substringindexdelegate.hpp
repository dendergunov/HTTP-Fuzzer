#ifndef SUBSTRINGINDEXDELEGATE_HPP
#define SUBSTRINGINDEXDELEGATE_HPP

#include "qstyleditemdelegate.h"

#include <QStyledItemDelegate>
#include <QtWidgets/QWidget>

class SubStringIndexDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

};

#endif // SUBSTRINGINDEXDELEGATE_HPP
