#ifndef QLISTTABLEWIDGET_HPP
#define QLISTTABLEWIDGET_HPP

#include <QtWidgets/QWidget>

namespace Ui {
class QListTableWidget;
}

class QListTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QListTableWidget(QWidget *parent = nullptr);
    ~QListTableWidget();

protected:

private slots:
    void on_addRowButton_clicked();

    void on_showCountButton_clicked();

    void on_deleteSelectedRowButton_clicked();

private:
    Ui::QListTableWidget *ui;
};

#endif // QLISTTABLEWIDGET_HPP
