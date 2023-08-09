#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QPlainTextEdit>

class Dialog : public QDialog
{
    Q_OBJECT
private:
    QCheckBox *checkBoxUnderline;
    QCheckBox *checkBoxItalic;
    QCheckBox *checkBoxBold;

    QRadioButton *radioButtonBlue;
    QRadioButton *radioButtonRad;
    QRadioButton *radioButtonBlack;

    QPlainTextEdit *plainTextEdit;

    QPushButton *btnOk;
    QPushButton *btnCancel;
    QPushButton *btnQuit;

    void initUi();
    void initSignalSlots();
private slots:
    void on_checkUnderline(bool checked);
    void on_checkItalic(bool checked);
    void on_checkBold(bool checked);
    void setTextFontColor();
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
