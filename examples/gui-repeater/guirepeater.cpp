#include "guirepeater.hpp"
#include "ui_guirepeater.h"
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
                                        << QStringLiteral("GET")
                                        << QStringLiteral("POST")
                                        );

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
        ui->replyStatusLabel->setText(statusCodeAndDescription);
    }

    ui->replyReadOnlyplainTextEdit->clear();

    if(reply->error() == QNetworkReply::NoError){
        ui->replyReadOnlyplainTextEdit->setPlainText(QString::fromUtf8(reply->readAll()));
        QMessageBox::information(this, tr("Request info"), tr("Request has been completed!"));
    } else {
        QMessageBox::information(this, tr("Request info"), tr("Request has been failed!"));
    }

    reply->deleteLater();
}
