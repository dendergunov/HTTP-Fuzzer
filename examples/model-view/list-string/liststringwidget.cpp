#include "liststringwidget.hpp"
#include "ui_liststringwidget.h"

#include <QMessageBox>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QDebug>
#include <QItemSelectionModel>

ListStringWidget::ListStringWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListStringWidget)
{
    ui->setupUi(this);

    ui->listView->setModel(&lsm_);
}

void ListStringWidget::on_showItemCountListWidgetButton_clicked()
{
    QMessageBox::information(this, tr("List Widget contains"), tr("List Widget contains %1 items").arg(ui->listWidget->count()));
}

void ListStringWidget::on_addItemToListWidgetButton_clicked()
{
    static int i = 0;
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(QStringLiteral("<item> %1").arg(i));
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(item);
    ++i;
}

void ListStringWidget::on_deleteItemListWidgetButton_clicked()
{
    QList<QListWidgetItem*> selected_items = ui->listWidget->selectedItems();
    for(QListWidgetItem *item: selected_items){
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

void ListStringWidget::on_addItemListViewButton_clicked()
{
    static int i = 0;
    lsm_.insertRow(lsm_.rowCount());
    QModelIndex index(lsm_.index(lsm_.rowCount()-1));
    lsm_.setData(index, QStringLiteral("<item> %1").arg(i));
    ++i;
}

void ListStringWidget::on_deleteItemListViewButton_clicked()
{
    QModelIndexList index_list = ui->listView->selectionModel()->selectedIndexes();
    if(!index_list.isEmpty())
        lsm_.removeRow(index_list.first().row());
}

void ListStringWidget::on_showItemCountListViewButton_clicked()
{
    QMessageBox::information(this, tr("QStringListModel"), tr("QStringListModel contains %1 items").arg(lsm_.rowCount()));
}
