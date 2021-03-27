#ifndef PAYLOADEDITORWIDGET_HPP
#define PAYLOADEDITORWIDGET_HPP

#include "payloadlistdelegate.hpp"
#include "substringindexdelegate.hpp"
#include "../repeater/requestheadermodel.hpp"
#include "payloadmodel.hpp"
#include "fuzzmanager.hpp"
#include "requestresultmodel.hpp"

#include <QtWidgets/QWidget>
#include <QPair>
#include <QThread>

namespace Ui {
class FuzzWidget;
}

namespace Fuzz{

class FuzzWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FuzzWidget(QWidget *parent = nullptr);
    ~FuzzWidget() override;

    void setRequestParameters(const QString& url, const QString& method, const QList<QPair<QByteArray, QByteArray>>& headers,
                              const QString& body);

    bool isRunning();
signals:
    void fuzzStarted(const QString& url, const QString& body, const QList<QPair<QByteArray, QByteArray>>& requestHeaders,
                     const QList<PayloadRow>& urlPayload, const QList<PayloadRow>& bodyPayload, const QString& method, int delay);
protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_urlSaveSelectionButton_clicked();

    void on_urlLineEdit_selectionChanged();

    void on_bodyPlainTextEdit_selectionChanged();

    void on_bodySaveSelectionButton_clicked();

    void on_addUrlPayloadButton_clicked();

    void on_deleteUrlPayloadButton_clicked();

    void on_deleteBodyPayloadButton_clicked();

    void on_addBodyPayloadButton_clicked();

    void on_fuzzCancelButton_clicked();
    void fuzzDone(const QString& result);
    void on_replyTableView_doubleClicked(const QModelIndex &index);

private:
    Ui::FuzzWidget *ui;
    Model::RequestHeaderModel *requestHeaderModel_;

    using start = int;
    using length = int;
    QPair<start, length> urlLastSelectionIndexes,
        urlSavedSelectionIndexes,
        bodyLastSelectionIndexes,
        bodySavedSelectionIndexes;

    Delegate::PayloadListDelegate *pld_;
    Delegate::SubStringIndexDelegate *ssid_;
    Model::PayloadModel *bodyPayloadModel_,
        *urlPayloadModel_;

    QThread* thread_;
    Fuzz::FuzzManager* fm_;
    Model::RequestResultModel *rrm_;
    bool running_ = false;
};

}
#endif // PAYLOADEDITORWIDGET_HPP
