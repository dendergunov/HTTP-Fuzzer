#include "fuzzwidget.hpp"
#include "./ui_fuzzwidget.h"

#include <QtWidgets/QMessageBox>

FuzzWidget::FuzzWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FuzzWidget)
{
    ui->setupUi(this);
}

FuzzWidget::~FuzzWidget()
{
    delete ui;
}


void FuzzWidget::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About programm"), tr("Simple HTTP Fuzzer. Edit requests, send it, check the result"));
}
