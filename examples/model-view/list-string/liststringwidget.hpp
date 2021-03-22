#ifndef LISTSTRINGWIDGET_HPP
#define LISTSTRINGWIDGET_HPP

#include <QtWidgets/QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class ListStringWidget; }
QT_END_NAMESPACE

class ListStringWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListStringWidget(QWidget *parent = nullptr);
    ~ListStringWidget() = default;

private slots:
    void on_showItemCountListWidgetButton_clicked();

    void on_addItemToListWidgetButton_clicked();

    void on_deleteItemListWidgetButton_clicked();

    void on_addItemListViewButton_clicked();

    void on_deleteItemListViewButton_clicked();

    void on_showItemCountListViewButton_clicked();

private:
    Ui::ListStringWidget *ui;
    QStringListModel lsm_;
};

#endif // LISTSTRINGWIDGET_HPP
