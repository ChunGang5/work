#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_checkBoxUnderline_clicked(bool checked);

    void on_checkBoxItalic_clicked(bool checked);

    void on_checkBoxBold_clicked(bool checked);

    // 定义字体样式颜色
    void set_text_font_color();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
