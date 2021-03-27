#ifndef GUIREPEATER_HPP
#define GUIREPEATER_HPP

#include "requestheadermodel.hpp"
#include "replyheadermodel.hpp"
#include "../fuzzer/fuzzwidget.hpp"

#include <QtWidgets/QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class GuiRepeater;}
QT_END_NAMESPACE

namespace Repeater{

class GuiRepeater : public QWidget
{
    Q_OBJECT
private:
    QNetworkAccessManager qnam_;
public:
    explicit GuiRepeater(QWidget *parent = nullptr);
    ~GuiRepeater();

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_sendRequestButton_clicked();
    void requestFinished(QNetworkReply* reply);

    void on_addRequestHeaderButon_clicked();

    void on_deleteRequetHeaderButton_clicked();

    void on_deleteAllRequestHeaderButton_clicked();

    void on_fuzzButton_clicked();

private:
    Ui::GuiRepeater *ui;
    Model::ReplyHeaderModel *replyHeaderModel_;
    Model::RequestHeaderModel *requestHeaderModel_;
    Fuzz::FuzzWidget *fuzzWidget_;
};

}
#endif // GUIREPEATER_HPP
