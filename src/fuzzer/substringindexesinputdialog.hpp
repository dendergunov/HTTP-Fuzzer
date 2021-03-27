#ifndef SUBSTRINGINDEXESINPUTDIALOG_HPP
#define SUBSTRINGINDEXESINPUTDIALOG_HPP

#include "customtypes.hpp"

#include <QtWidgets/QDialog>

namespace Ui {
class SubStringIndexesInputDialog;
}

namespace Fuzz{

class SubStringIndexesInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SubStringIndexesInputDialog(QWidget *parent = nullptr);
    explicit SubStringIndexesInputDialog(QWidget *parent = nullptr, const substringCoordinates& coordinates = {0,0});
    ~SubStringIndexesInputDialog();

    substringCoordinates getCoordinates();

private slots:
    void on_startIndexSpinBox_valueChanged(int arg1);

    void on_endIndexSpinBox_valueChanged(int arg1);

private:
    Ui::SubStringIndexesInputDialog *ui;
};
}
#endif // SUBSTRINGINDEXESINPUTDIALOG_HPP
