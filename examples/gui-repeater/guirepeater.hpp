#ifndef GUIREPEATER_HPP
#define GUIREPEATER_HPP

#include <QtWidgets/QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class GuiRepeater;}
QT_END_NAMESPACE

class GuiRepeater : public QWidget
{
    Q_OBJECT
private:
    QNetworkAccessManager qnam_;
public:
    explicit GuiRepeater(QWidget *parent = nullptr);
    ~GuiRepeater();

protected:

private slots:
    void on_sendRequestButton_clicked();
    void requestFinished(QNetworkReply* reply);

private:
    Ui::GuiRepeater *ui;
};

#endif // GUIREPEATER_HPP
