#include "editpayloaddialog.hpp"
#include "ui_editpayloaddialog.h"

EditPayloadDialog::EditPayloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPayloadDialog)
{
    ui->setupUi(this);

}

EditPayloadDialog::~EditPayloadDialog()
{
    delete ui;
}
