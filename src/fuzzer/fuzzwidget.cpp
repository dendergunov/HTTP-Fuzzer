#include "fuzzwidget.hpp"
#include "ui_fuzzwidget.h"
#include "payloadmodel.hpp"
#include "payloadlistdelegate.hpp"
#include "substringindexdelegate.hpp"
#include "fuzzmanager.hpp"
#include "requestresultmodel.hpp"

#include <QMessageBox>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QInputDialog>

namespace Fuzz{


FuzzWidget::FuzzWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FuzzWidget),
    requestHeaderModel_(new Model::RequestHeaderModel),
    pld_(new Delegate::PayloadListDelegate),
    ssid_(new Delegate::SubStringIndexDelegate),
    bodyPayloadModel_(new Model::PayloadModel),
    urlPayloadModel_(new Model::PayloadModel),
    thread_(new QThread{this}),
    fm_(new Fuzz::FuzzManager),
    rrm_(new Model::RequestResultModel)
{
    ui->setupUi(this);

    ui->requestMethodComboBox->addItems(QStringList()
                                        << QStringLiteral("GET") << QStringLiteral("POST")
                                        << QStringLiteral("HEAD") << QStringLiteral("PUT")
                                        << QStringLiteral("DELETE") << QStringLiteral("CONNECT")
                                        << QStringLiteral("OPTIONS") << QStringLiteral("TRACE")
                                        << QStringLiteral("PATCH")
                                        );

    ui->urlPayloadTableView->setModel(urlPayloadModel_);
    ui->urlPayloadTableView->setItemDelegateForColumn(2, pld_);
    ui->urlPayloadTableView->setItemDelegateForColumn(0, ssid_);
    ui->urlPayloadTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->urlPayloadTableView->horizontalHeader()->setStretchLastSection(true);


    ui->bodyPayloadTableView->setModel(bodyPayloadModel_);
    ui->bodyPayloadTableView->setItemDelegateForColumn(2, pld_);
    ui->bodyPayloadTableView->setItemDelegateForColumn(0, ssid_);
    ui->bodyPayloadTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->bodyPayloadTableView->horizontalHeader()->setStretchLastSection(true);

    ui->requestHeadersTableView->setModel(requestHeaderModel_);
    ui->requestHeadersTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    thread_->start();
    fm_->moveToThread(thread_);

    QSortFilterProxyModel *filterModel_ = new QSortFilterProxyModel;
    filterModel_->setSourceModel(rrm_);
    ui->replyTableView->setModel(filterModel_);
    ui->replyTableView->setSortingEnabled(true);
    ui->replyTableView->horizontalHeader()->setStretchLastSection(true);

    connect(thread_, &QThread::finished, fm_, &QObject::deleteLater);
    connect(fm_, &FuzzManager::progressChanged, ui->progressBar, &QProgressBar::setValue);
    connect(this, &FuzzWidget::fuzzStarted, fm_, &FuzzManager::fuzzStart);
    connect(fm_, &FuzzManager::done, this, &FuzzWidget::fuzzDone);

    connect(fm_, &FuzzManager::replyProcessed, rrm_, &Model::RequestResultModel::appendRequestResult);
    connect(fm_, &FuzzManager::fuzzRestarted, rrm_, &Model::RequestResultModel::clearData);
}

FuzzWidget::~FuzzWidget()
{
    thread_->quit();
    thread_->wait();

    delete ui;
}

void FuzzWidget::closeEvent(QCloseEvent *event)
{
    if(running_){
        ui->fuzzCancelButton->click();
        event->ignore();
    } else {
        event->accept();
    }
}

void FuzzWidget::on_urlSaveSelectionButton_clicked()
{
    if(urlLastSelectionIndexes.second > 0){
        urlSavedSelectionIndexes.first = urlLastSelectionIndexes.first;
        urlSavedSelectionIndexes.second = urlLastSelectionIndexes.second;
        ui->urlSavedSelectionLabel->setText(QStringLiteral("Selection: [") + QString::number(urlSavedSelectionIndexes.first)
                                            + QStringLiteral(";") + QString::number(urlSavedSelectionIndexes.first + urlSavedSelectionIndexes.second - 1)
                                            + QStringLiteral("]"));
    }

}

void FuzzWidget::on_urlLineEdit_selectionChanged()
{
    int selectionStart = ui->urlLineEdit->selectionStart();
    if(selectionStart != -1){
        int selectionLength = ui->urlLineEdit->selectionLength();
        urlLastSelectionIndexes.first = selectionStart;
        urlLastSelectionIndexes.second = selectionLength;
    }
}

void FuzzWidget::on_bodyPlainTextEdit_selectionChanged()
{
    int selectionStart = ui->bodyPlainTextEdit->textCursor().selectionStart();
    int selectionEnd = ui->bodyPlainTextEdit->textCursor().selectionEnd();

    bodyLastSelectionIndexes.first = selectionStart;
    bodyLastSelectionIndexes.second = selectionEnd - selectionStart;
}

void FuzzWidget::on_bodySaveSelectionButton_clicked()
{
    if(bodyLastSelectionIndexes.second > 0){
        bodySavedSelectionIndexes.first = bodyLastSelectionIndexes.first;
        bodySavedSelectionIndexes.second = bodyLastSelectionIndexes.second;
        ui->bodySavedSelectionLabel->setText(QStringLiteral("Selection: [") + QString::number(bodySavedSelectionIndexes.first)
                                             + QStringLiteral(";") + QString::number(bodySavedSelectionIndexes.first + bodySavedSelectionIndexes.second - 1)
                                             + QStringLiteral("]"));
    }

}

void FuzzWidget::on_addUrlPayloadButton_clicked()
{
    if(urlSavedSelectionIndexes.second > 0){
        Model::PayloadModel *model = dynamic_cast<Model::PayloadModel*>(ui->urlPayloadTableView->model());

        QVariant stringIndexes;
        substringCoordinates coordinates(QPair<int,int>(urlSavedSelectionIndexes.first, urlSavedSelectionIndexes.second));
        stringIndexes.setValue(coordinates);
        if(model->isSubStringOverlap(coordinates)){
            QMessageBox::critical(this, tr("Set payload substring overlaps other substirng!"),
                                  tr("Setting substring indexes that overlap other substring indexes is not allowed!"));
            return;
        }
        model->insertRow(model->rowCount());
        model->setData(model->index(model->rowCount()-1, 0), stringIndexes);
    }
}

void FuzzWidget::on_deleteUrlPayloadButton_clicked()
{
    QModelIndexList deletionIndexes(ui->urlPayloadTableView->selectionModel()->selectedIndexes());

    if(!deletionIndexes.isEmpty()){
        ui->urlPayloadTableView->model()->removeRow(deletionIndexes.first().row());
    }
}

void FuzzWidget::on_deleteBodyPayloadButton_clicked()
{
    QModelIndexList deletionIndexes(ui->bodyPayloadTableView->selectionModel()->selectedIndexes());

    if(!deletionIndexes.isEmpty()){
        ui->bodyPayloadTableView->model()->removeRow(deletionIndexes.first().row());
    }
}

void FuzzWidget::on_addBodyPayloadButton_clicked()
{
    if(bodySavedSelectionIndexes.second > 0){
        Model::PayloadModel *model = dynamic_cast<Model::PayloadModel*>(ui->bodyPayloadTableView->model());

        QVariant stringIndexes;
        substringCoordinates coordinates(bodySavedSelectionIndexes.first, bodySavedSelectionIndexes.second);
        stringIndexes.setValue(coordinates);
        if(model->isSubStringOverlap(coordinates)){
            QMessageBox::critical(this, tr("Set payload substring overlaps other substirng!"),
                                  tr("Setting substring indexes that overlap other substring indexes is not allowed!"));
            return;
        }
        model->insertRow(model->rowCount());
        model->setData(model->index(model->rowCount()-1, 0), stringIndexes);
    }
}

void FuzzWidget::setRequestParameters(const QString& url, const QString& method, const QList<QPair<QByteArray, QByteArray>>& headers,
                          const QString& body)
{
    ui->urlLineEdit->setText(url);
    int index = ui->requestMethodComboBox->findText(method);
    ui->requestMethodComboBox->setCurrentIndex(index);
    requestHeaderModel_->setRequestHeaders(headers);
    ui->bodyPlainTextEdit->setPlainText(body);
}

void FuzzWidget::on_fuzzCancelButton_clicked()
{
    if(!running_){
        ui->fuzzCancelButton->setText(tr("Cancel"));

        fm_->setCancelled(false);

        emit fuzzStarted(ui->urlLineEdit->text(), ui->bodyPlainTextEdit->toPlainText(),
                         requestHeaderModel_->requestHeaders(), urlPayloadModel_->payloadRows(),
                         bodyPayloadModel_->payloadRows(), ui->requestMethodComboBox->currentText(),
                         ui->sendDeaySpinBox->value());

        running_ = true;
    } else {
        ui->fuzzCancelButton->setEnabled(false);
        fm_->setCancelled(true);
    }
}

void FuzzWidget::fuzzDone(const QString& result)
{
    QMessageBox::information(this, tr("Fuzz result"), result);
    ui->fuzzCancelButton->setEnabled(true);
    ui->fuzzCancelButton->setText(tr("Fuzz"));
    running_ = false;
}

bool FuzzWidget::isRunning()
{
    return running_;
}

}

void Fuzz::FuzzWidget::on_replyTableView_doubleClicked(const QModelIndex &index)
{
    if(index.column() > 0)
        QInputDialog::getMultiLineText(this, tr("View reply content"),
                                       index.model()->headerData(index.column(), Qt::Horizontal).toString(), index.data().toString());
}
