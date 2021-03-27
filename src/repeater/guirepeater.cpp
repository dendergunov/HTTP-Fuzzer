#include "guirepeater.hpp"
#include "ui_guirepeater.h"
#include "replyheadermodel.hpp"
#include "requestheadermodel.hpp"
#include "../fuzzer/fuzzwidget.hpp"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QMessageBox>
#include <QString>
#include <QByteArray>
#include <QVariant>
#include <QChar>

namespace Repeater{

GuiRepeater::GuiRepeater(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuiRepeater),
    replyHeaderModel_(new Model::ReplyHeaderModel),
    requestHeaderModel_(new Model::RequestHeaderModel),
    fuzzWidget_(new Fuzz::FuzzWidget)
{
    ui->setupUi(this);

    ui->requestMethodComboBox->addItems(QStringList()
                                        << QStringLiteral("GET") << QStringLiteral("POST")
                                        << QStringLiteral("HEAD") << QStringLiteral("PUT")
                                        << QStringLiteral("DELETE") << QStringLiteral("CONNECT")
                                        << QStringLiteral("OPTIONS") << QStringLiteral("TRACE")
                                        << QStringLiteral("PATCH")
                                        );

    ui->replyHeadersTableView->setModel(replyHeaderModel_);
    ui->replyHeadersTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->replyHeadersTableView->horizontalHeader()->setStretchLastSection(true);
    ui->replyHeadersTableView->resizeRowsToContents();

    ui->requestHeadersTableView->setModel(requestHeaderModel_);
    ui->requestHeadersTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(&qnam_, &QNetworkAccessManager::finished, this, &GuiRepeater::requestFinished);
}

GuiRepeater::~GuiRepeater()
{
    delete ui;
}

void GuiRepeater::closeEvent(QCloseEvent *event)
{
    if(fuzzWidget_->isRunning())
        event->ignore();
    else {
        fuzzWidget_->close();
        event->accept();
    }
}

void GuiRepeater::on_sendRequestButton_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl(ui->urlLineEdit->text()));

    ui->sendRequestButton->setEnabled(false);
    ui->fuzzButton->setEnabled(false);

    qnam_.sendCustomRequest(request, ui->requestMethodComboBox->currentText().toUtf8(), ui->requestBodyPlainTextEdit->toPlainText().toUtf8());
}

void GuiRepeater::requestFinished(QNetworkReply *reply)
{
    QString statusCodeAndDescription(QStringLiteral(" "));
    QVariant statusCode(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)),
        statusDescription(reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute));
    if(!statusCode.isNull() && !statusDescription.isNull()){
        statusCodeAndDescription.prepend(statusCode.toString()).append(statusDescription.toString());
        ui->replyStatusCodeDescriptionLabel->setText(statusCodeAndDescription);
    }

    Model::ReplyHeaderModel *replyHeaderModel = dynamic_cast<Model::ReplyHeaderModel*>(ui->replyHeadersTableView->model());

    if(reply->error() == QNetworkReply::NoError){
        ui->replyBodyPlainTextEdit->setPlainText(QString::fromUtf8(reply->readAll()));
        replyHeaderModel->setReplyHeaders(reply->rawHeaderPairs());
    } else {
        ui->replyBodyPlainTextEdit->clear();
        replyHeaderModel->setReplyHeaders({});
    }

    reply->deleteLater();

    ui->sendRequestButton->setEnabled(true);
    ui->fuzzButton->setEnabled(true);
}

void GuiRepeater::on_addRequestHeaderButon_clicked()
{
    ui->requestHeadersTableView->model()->insertRow(ui->requestHeadersTableView->model()->rowCount());
}

void GuiRepeater::on_deleteRequetHeaderButton_clicked()
{
    QModelIndexList deletionIndexes(ui->requestHeadersTableView->selectionModel()->selectedRows());

    if(!deletionIndexes.isEmpty()){
        ui->requestHeadersTableView->model()->removeRow(deletionIndexes.first().row());
    }
}

void GuiRepeater::on_deleteAllRequestHeaderButton_clicked()
{
    ui->requestHeadersTableView->model()->removeRows(0, ui->requestHeadersTableView->model()->rowCount());
}

}

void Repeater::GuiRepeater::on_fuzzButton_clicked()
{
    fuzzWidget_->setRequestParameters(ui->urlLineEdit->text(), ui->requestMethodComboBox->currentText(),
                                      requestHeaderModel_->requestHeaders(), ui->requestBodyPlainTextEdit->toPlainText());
    fuzzWidget_->show();
}
