#ifndef EDITPAYLOADDIALOG_HPP
#define EDITPAYLOADDIALOG_HPP

#include <QtWidgets/QDialog>

namespace Ui {
class EditPayloadDialog;
}

class EditPayloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPayloadDialog(QWidget *parent = nullptr);
    ~EditPayloadDialog();

private:
    Ui::EditPayloadDialog *ui;
};

#endif // EDITPAYLOADDIALOG_HPP
