#include "payloadwidget.hpp"
#include "ui_payloadwidget.h"
#include "editpayloaddialog.hpp"

#include <QStringListModel>
#include <QInputDialog>

PayloadWidget::PayloadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PayloadWidget)
{
    ui->setupUi(this);

    ui->payloadListView->setModel(new QStringListModel{ui->payloadListView});
}

PayloadWidget::~PayloadWidget()
{
    delete ui;
}

void PayloadWidget::on_newPayloadButton_clicked()
{
    bool ok;
    QString multiLinePayload = QInputDialog::getMultiLineText(this, QStringLiteral("New Payload"), QStringLiteral("Add each payload on new line"), {}, &ok);
    if(ok){
        QStringList payloadList = multiLinePayload.split(QStringLiteral("\n"));
        dynamic_cast<QStringListModel*>(ui->payloadListView->model())->setStringList(payloadList);
    }
}

void PayloadWidget::on_editPayloadButton_clicked()
{
    bool ok;

    QStringListModel *model = dynamic_cast<QStringListModel*>(ui->payloadListView->model());
    QStringList payloadList = model->stringList();
    QString multiLinePayload = QInputDialog::getMultiLineText(this, QStringLiteral("Edit Payload"),
                                                              QStringLiteral("Each payload is placed on new line"),
                                                              payloadList.join(QStringLiteral("\n")), &ok);
    if(ok){
        payloadList = multiLinePayload.split(QStringLiteral("\n"));
        model->setStringList(payloadList);
    }
}

void PayloadWidget::on_clearPayloadButton_clicked()
{
    QStringListModel *model = dynamic_cast<QStringListModel*>(ui->payloadListView->model());
    model->setStringList({});
}
