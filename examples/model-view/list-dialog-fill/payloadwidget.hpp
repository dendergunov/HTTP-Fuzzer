#ifndef PAYLOADWIDGET_HPP
#define PAYLOADWIDGET_HPP

#include <QtWidgets/QWidget>
#include <QStringListModel>

namespace Ui {
class PayloadWidget;
}

class PayloadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PayloadWidget(QWidget *parent = nullptr);
    ~PayloadWidget();


private slots:
    void on_newPayloadButton_clicked();

    void on_editPayloadButton_clicked();

    void on_clearPayloadButton_clicked();

private:
    Ui::PayloadWidget *ui;
};

#endif // PAYLOADWIDGET_HPP
