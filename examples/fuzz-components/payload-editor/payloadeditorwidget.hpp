#ifndef PAYLOADEDITORWIDGET_HPP
#define PAYLOADEDITORWIDGET_HPP

#include "payloadlistdelegate.hpp"
#include "substringindexdelegate.hpp"

#include <QtWidgets/QWidget>
#include <QPair>

namespace Ui {
class PayloadEditorWidget;
}

class PayloadEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PayloadEditorWidget(QWidget *parent = nullptr);
    ~PayloadEditorWidget();

private slots:
    void on_urlSaveSelectionButton_clicked();

    void on_urlLineEdit_selectionChanged();

    void on_bodyPlainTextEdit_selectionChanged();

    void on_bodySaveSelectionButton_clicked();

    void on_addUrlPayloadButton_clicked();

    void on_deleteUrlPayloadButton_clicked();

    void on_deleteBodyPayloadButton_clicked();

    void on_addBodyPayloadButton_clicked();

private:
    Ui::PayloadEditorWidget *ui;

    bool isFuzzRunning_ = false;

    using start = int;
    using length = int;
    QPair<start, length> urlLastSelectionIndexes,
        urlSavedSelectionIndexes,
        bodyLastSelectionIndexes,
        bodySavedSelectionIndexes;

    PayloadListDelegate *pld_;
    SubStringIndexDelegate *ssid_;
};

#endif // PAYLOADEDITORWIDGET_HPP
