#include "qlisttablewidget.hpp"
#include "ui_qlisttablewidget.h"
#include "pairstringmodel.hpp"

#include <QAbstractItemModel>
#include <QMessageBox>

QListTableWidget::QListTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QListTableWidget)
{
    ui->setupUi(this);

    ui->pairStringTableView->setModel(new PairStringModel{ui->pairStringTableView});
    ui->pairStringTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->pairStringTableView->model()->insertRow(0);
}

QListTableWidget::~QListTableWidget()
{
    delete ui;
}

void QListTableWidget::on_addRowButton_clicked()
{
    QAbstractItemModel *model =  ui->pairStringTableView->model();
    model->insertRow(model->rowCount());
}

void QListTableWidget::on_showCountButton_clicked()
{
    QMessageBox::information(this, tr("Table informaiton"), tr("Table row count: %1").arg(ui->pairStringTableView->model()->rowCount()));
}

void QListTableWidget::on_deleteSelectedRowButton_clicked()
{
    QModelIndexList deletionIndexes(ui->pairStringTableView->selectionModel()->selectedRows());

    if(!deletionIndexes.isEmpty()){
        ui->pairStringTableView->model()->removeRow(deletionIndexes.first().row());
    }
}
