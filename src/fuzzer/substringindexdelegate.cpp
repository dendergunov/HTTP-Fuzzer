#include "substringindexdelegate.hpp"
#include "substringindexesinputdialog.hpp"
#include "customtypes.hpp"
#include "payloadmodel.hpp"

#include <QMessageBox>

namespace Delegate{
QWidget* SubStringIndexDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    QVariant data = index.data(Qt::EditRole);
    if(!data.canConvert<substringCoordinates>())
        return QStyledItemDelegate::createEditor(parent, option, index);


    Fuzz::SubStringIndexesInputDialog dialog(parent, data.value<substringCoordinates>());

    if(dialog.exec() == QDialog::Accepted){
        Model::PayloadModel *model = dynamic_cast<Model::PayloadModel*>(const_cast<QAbstractItemModel*>(index.model()));
        substringCoordinates coordinates(dialog.getCoordinates());
        if(model->isSubStringOverlap(coordinates, index.row())){
            QMessageBox::critical(parent, tr("Set payload substring overlaps other substirng!"),
                                  tr("Setting substring indexes that overlap other substring indexes is not allowed!"));
            return nullptr;
        }

        QVariant store;
        store.setValue(coordinates);
        const_cast<QAbstractItemModel*>(index.model())->setData(index, store, Qt::EditRole);
    }

    return nullptr;
}
}
