#include "fuzzwidget.hpp"
#include "ui_fuzzwidget.h"

#include <QtGui/QCloseEvent>
#include <QMessageBox>
#include <QSortFilterProxyModel>


FuzzWidget::FuzzWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FuzzWidget),
    thread_(new QThread{this}),
    fm_(new FuzzManager),
    rrm_(new RequestResultModel)
{
    ui->setupUi(this);

    thread_->start();
    fm_->moveToThread(thread_);

    QSortFilterProxyModel *filterModel_ = new QSortFilterProxyModel;
    filterModel_->setSourceModel(rrm_);
    ui->replyTableView->setModel(filterModel_);
    ui->replyTableView->setSortingEnabled(true);
    ui->replyTableView->horizontalHeader()->setStretchLastSection(true);

    connect(thread_, &QThread::finished, fm_, &QObject::deleteLater);
    connect(fm_, &FuzzManager::progressChanged, ui->progressBar, &QProgressBar::setValue);
    connect(this, &FuzzWidget::fuzzStarted, fm_, &FuzzManager::fuzz);
    connect(fm_, &FuzzManager::done, this, &FuzzWidget::fuzzDone);

    connect(fm_, &FuzzManager::replyProcessed, rrm_, &RequestResultModel::appendRequestResult);
    connect(fm_, &FuzzManager::fuzzRestarted, rrm_, &RequestResultModel::clearData);
}

FuzzWidget::~FuzzWidget()
{
    thread_->quit();
    thread_->wait();

    delete ui;
}

void FuzzWidget::closeEvent(QCloseEvent *event)
{
    if(running_){
        ui->fuzzCancelButton->click();
        event->ignore();
    } else {
        event->accept();
    }
}

void FuzzWidget::on_fuzzCancelButton_clicked()
{
    if(!running_){
        ui->fuzzCancelButton->setText(tr("Cancel"));

        fm_->setCancelled(false);

        emit fuzzStarted(ui->requestsToSendSpinBox->value(),
                         ui->sendDeaySpinBox->value());

        running_ = true;
    } else {
        ui->fuzzCancelButton->setEnabled(false);
        fm_->setCancelled(true);
    }
}

void FuzzWidget::fuzzDone(const QString& result)
{
    QMessageBox::information(this, tr("Fuzz result"), result);
    ui->fuzzCancelButton->setEnabled(true);
    ui->fuzzCancelButton->setText(tr("Fuzz"));
    running_ = false;
}
