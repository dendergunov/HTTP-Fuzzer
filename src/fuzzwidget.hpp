#ifndef FUZZWIDGET_HPP
#define FUZZWIDGET_HPP

#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class FuzzWidget; }
QT_END_NAMESPACE

class FuzzWidget : public QMainWindow
{
    Q_OBJECT

public:
    FuzzWidget(QWidget *parent = nullptr);
    ~FuzzWidget();

private slots:
    void on_actionAbout_triggered();

private:
    Ui::FuzzWidget *ui;
};
#endif // FUZZWIDGET_HPP
