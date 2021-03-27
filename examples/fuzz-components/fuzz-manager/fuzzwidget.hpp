#ifndef FUZZWIDGET_HPP
#define FUZZWIDGET_HPP

#include "fuzzmanager.hpp"
#include "requestresultmodel.hpp"

#include <QtWidgets/QWidget>
#include <QThread>

namespace Ui {
class FuzzWidget;
}

class FuzzWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FuzzWidget(QWidget *parent = nullptr);
    ~FuzzWidget() override;

signals:
    void fuzzStarted(int count, int delay);

protected:
    void closeEvent(QCloseEvent* event) override;
private slots:
    void on_fuzzCancelButton_clicked();
    void fuzzDone(const QString& result);
private:
    Ui::FuzzWidget *ui;
    QThread* thread_;
    FuzzManager* fm_;
    RequestResultModel *rrm_;
    bool running_ = false;
};

#endif // FUZZWIDGET_HPP
