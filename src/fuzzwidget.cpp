#include "fuzzwidget.hpp"
#include "./ui_fuzzwidget.h"

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

