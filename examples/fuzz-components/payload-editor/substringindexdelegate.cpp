#include "substringindexdelegate.hpp"
#include "substringindexesinputdialog.hpp"
#include "customtypes.hpp"

QWidget* SubStringIndexDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    QVariant data = index.data(Qt::EditRole);
    if(!data.canConvert<substringCoordinates>())
        return QStyledItemDelegate::createEditor(parent, option, index);


    SubStringIndexesInputDialog dialog(parent, data.value<substringCoordinates>());

    if(dialog.exec() == QDialog::Accepted){
        substringCoordinates coordinates(dialog.getCoordinates());
        QVariant store;
        store.setValue(coordinates);
        const_cast<QAbstractItemModel*>(index.model())->setData(index, store, Qt::EditRole);
    }

    return nullptr;
}
