#include "guirepeater.hpp"
#include "ui_guirepeater.h"
#include "replyheadermodel.hpp"
#include "requestheadermodel.hpp"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QMessageBox>
#include <QString>
#include <QByteArray>
#include <QVariant>
#include <QChar>

GuiRepeater::GuiRepeater(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuiRepeater)
{
    ui->setupUi(this);

    ui->requestMethodcomboBox->addItems(QStringList()
                                        << QStringLiteral("GET") << QStringLiteral("POST")
                                        << QStringLiteral("HEAD") << QStringLiteral("PUT")
                                        << QStringLiteral("DELETE") << QStringLiteral("CONNECT")
                                        << QStringLiteral("OPTIONS") << QStringLiteral("TRACE")
                                        << QStringLiteral("PATCH")
                                        );

    ui->replyHeadersTableView->setModel(new ReplyHeaderModel{ui->replyHeadersTableView});
    ui->replyHeadersTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->replyHeadersTableView->horizontalHeader()->setStretchLastSection(true);
    ui->replyHeadersTableView->resizeRowsToContents();

    ui->requestHeadersTableView->setModel(new RequestHeaderModel{ui->requestHeadersTableView});
    ui->requestHeadersTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(&qnam_, &QNetworkAccessManager::finished, this, &GuiRepeater::requestFinished);
}

GuiRepeater::~GuiRepeater()
{
    delete ui;
}

void GuiRepeater::on_sendRequestButton_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl(ui->urlLineEdit->text()));

    qnam_.sendCustomRequest(request, ui->requestMethodcomboBox->currentText().toUtf8(), ui->requestBodyPlainTextEdit->toPlainText().toUtf8());
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

    ReplyHeaderModel *replyHeaderModel = dynamic_cast<ReplyHeaderModel*>(ui->replyHeadersTableView->model());

    if(reply->error() == QNetworkReply::NoError){
        ui->replyBodyPlainTextEdit->setPlainText(QString::fromUtf8(reply->readAll()));
        replyHeaderModel->setReplyHeaders(reply->rawHeaderPairs());
    } else {
        ui->replyBodyPlainTextEdit->clear();
        replyHeaderModel->setReplyHeaders({});
    }

    reply->deleteLater();
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
