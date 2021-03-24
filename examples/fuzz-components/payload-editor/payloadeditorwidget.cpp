#include "payloadeditorwidget.hpp"
#include "ui_payloadeditorwidget.h"
#include "payloadmodel.hpp"
#include "payloadlistdelegate.hpp"
#include "substringindexdelegate.hpp"

#include <QDebug>

PayloadEditorWidget::PayloadEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PayloadEditorWidget),
    pld_(new PayloadListDelegate{this}),
    ssid_(new SubStringIndexDelegate{this})
{
    ui->setupUi(this);

    ui->urlPayloadTableView->setModel(new PayloadModel{ui->urlPayloadTableView});
    ui->urlPayloadTableView->setItemDelegateForColumn(2, pld_);
    ui->urlPayloadTableView->setItemDelegateForColumn(0, ssid_);

    ui->bodyPayloadTableView->setModel(new PayloadModel{ui->bodyPayloadTableView});
    ui->bodyPayloadTableView->setItemDelegateForColumn(2, pld_);
    ui->bodyPayloadTableView->setItemDelegateForColumn(0, ssid_);
}

PayloadEditorWidget::~PayloadEditorWidget()
{
    delete ui;
}

void PayloadEditorWidget::on_urlSaveSelectionButton_clicked()
{
    if(urlLastSelectionIndexes.second > 0){
        urlSavedSelectionIndexes.first = urlLastSelectionIndexes.first;
        urlSavedSelectionIndexes.second = urlLastSelectionIndexes.second;
        ui->urlSavedSelectionLabel->setText(QStringLiteral("Selection: [") + QString::number(urlSavedSelectionIndexes.first)
                                            + QStringLiteral(";") + QString::number(urlSavedSelectionIndexes.first + urlSavedSelectionIndexes.second - 1)
                                            + QStringLiteral("]"));
    }

}

void PayloadEditorWidget::on_urlLineEdit_selectionChanged()
{
    int selectionStart = ui->urlLineEdit->selectionStart();
    if(selectionStart != -1){
        int selectionLength = ui->urlLineEdit->selectionLength();
        urlLastSelectionIndexes.first = selectionStart;
        urlLastSelectionIndexes.second = selectionLength;
    }
}

void PayloadEditorWidget::on_bodyPlainTextEdit_selectionChanged()
{
    int selectionStart = ui->bodyPlainTextEdit->textCursor().selectionStart();
    int selectionEnd = ui->bodyPlainTextEdit->textCursor().selectionEnd();

    bodyLastSelectionIndexes.first = selectionStart;
    bodyLastSelectionIndexes.second = selectionEnd - selectionStart;
}

void PayloadEditorWidget::on_bodySaveSelectionButton_clicked()
{
    if(bodyLastSelectionIndexes.second > 0){
        bodySavedSelectionIndexes.first = bodyLastSelectionIndexes.first;
        bodySavedSelectionIndexes.second = bodyLastSelectionIndexes.second;
        ui->bodySavedSelectionLabel->setText(QStringLiteral("Selection: [") + QString::number(bodySavedSelectionIndexes.first)
                                             + QStringLiteral(";") + QString::number(bodySavedSelectionIndexes.first + bodySavedSelectionIndexes.second - 1)
                                             + QStringLiteral("]"));
    }

}

void PayloadEditorWidget::on_addUrlPayloadButton_clicked()
{
    if(urlSavedSelectionIndexes.second > 0){
        QAbstractItemModel *model = ui->urlPayloadTableView->model();
        model->insertRow(model->rowCount());
        QVariant stringIndexes;
        stringIndexes.setValue(QPair<int,int>(urlSavedSelectionIndexes.first, urlSavedSelectionIndexes.second));
        model->setData(model->index(model->rowCount()-1, 0), stringIndexes);
    }
}

void PayloadEditorWidget::on_deleteUrlPayloadButton_clicked()
{
    QModelIndexList deletionIndexes(ui->urlPayloadTableView->selectionModel()->selectedIndexes());

    if(!deletionIndexes.isEmpty()){
        ui->urlPayloadTableView->model()->removeRow(deletionIndexes.first().row());
    }
}

void PayloadEditorWidget::on_deleteBodyPayloadButton_clicked()
{
    QModelIndexList deletionIndexes(ui->bodyPayloadTableView->selectionModel()->selectedIndexes());

    if(!deletionIndexes.isEmpty()){
        ui->bodyPayloadTableView->model()->removeRow(deletionIndexes.first().row());
    }
}

void PayloadEditorWidget::on_addBodyPayloadButton_clicked()
{
    if(bodySavedSelectionIndexes.second > 0){
        QAbstractItemModel *model = ui->bodyPayloadTableView->model();
        model->insertRow(model->rowCount());
        QVariant stringIndexes;
        stringIndexes.setValue(QPair<int,int>(bodySavedSelectionIndexes.first, bodySavedSelectionIndexes.second));
        model->setData(model->index(model->rowCount()-1, 0), stringIndexes);
    }
}

void PayloadEditorWidget::on_urlLineEdit_editingFinished()
{
    qDebug() << "Finished";
}
