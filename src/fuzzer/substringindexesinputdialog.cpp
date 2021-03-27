#include "substringindexesinputdialog.hpp"
#include "ui_substringindexesinputdialog.h"

namespace Fuzz{
SubStringIndexesInputDialog::SubStringIndexesInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubStringIndexesInputDialog)
{
    ui->setupUi(this);
}

SubStringIndexesInputDialog::SubStringIndexesInputDialog(QWidget *parent, const substringCoordinates& coordinates) :
    QDialog(parent),
    ui(new Ui::SubStringIndexesInputDialog)
{
    ui->setupUi(this);

    ui->startIndexSpinBox->setValue(coordinates.first);
    ui->endIndexSpinBox->setValue(coordinates.first + coordinates.second - 1);
}

SubStringIndexesInputDialog::~SubStringIndexesInputDialog()
{
    delete ui;
}

substringCoordinates SubStringIndexesInputDialog::getCoordinates()
{
    int startIndex = ui->startIndexSpinBox->value();
    int length = ui->endIndexSpinBox->value() - startIndex + 1;
    return substringCoordinates(startIndex, length);
}

void SubStringIndexesInputDialog::on_startIndexSpinBox_valueChanged(int arg1)
{
    ui->endIndexSpinBox->setMinimum(arg1);
}

void SubStringIndexesInputDialog::on_endIndexSpinBox_valueChanged(int arg1)
{
    ui->startIndexSpinBox->setMaximum(arg1);
}
}
